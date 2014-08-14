#include "ThreadImpl.h"
#include <iostream>

CThreadImpl::CThreadImpl()
    :   m_bStarted(false)
    ,   m_bRunning(false)
    ,   m_bAbort(false)
{
}

CThreadImpl::~CThreadImpl()
{
    // Если не была вызвана Stop(), вызываем ее
    if(m_bStarted && !m_bAbort)
        Stop();
}

void CThreadImpl::Start()
{
    // Устанавливаем флаг выполнения
    m_Mutex.lock();
    {
        m_bStarted = true;
        m_bRunning = true;

    }
    m_Mutex.unlock();;

    this->start();
}

void CThreadImpl::Stop()
{
    Release(true);

    this->quit();
    this->wait();
}

bool CThreadImpl::IsRunning() const
{
	return m_bRunning;
}

void CThreadImpl::Suspend()
{
    m_bRunning = false;
}

void CThreadImpl::Resume()
{
    m_bRunning = true;

    Release();
}

void CThreadImpl::Release(bool bAbort)
{
    m_Mutex.lock();

    if(bAbort)
        m_bAbort = true;

    m_Mutex.unlock();
    m_RunCondition.wakeAll();
}

void CThreadImpl::run()
{
    // Вызов функции перед бесконечным циклом
    PrepareWork();

    while(true)
    {
        // Блокируем поток, если он приостановлен
        {
            m_Mutex.lock();
            if(!m_bRunning)
			{
                m_RunCondition.wait(&m_Mutex);
				m_bRunning = true;
			}
            m_Mutex.unlock();
        }

        // Корректно завершаем поток, если он прерван
        if(m_bAbort)
            break;

        // Делаем полезную работу
        DoWork();
    }

	// Вызов пользовательской функции перед завершением потока
	DoOnStop();
}
