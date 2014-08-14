#ifndef THREADIMPL_H
#define THREADIMPL_H


#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include "Thread.hpp"

//! Общая реализация интерфейса
class CThreadImpl : public IThread, public QThread
{

protected:
    bool								m_bStarted;     //!< Поток был запущен
    bool								m_bRunning;     //!< Флаг выполнения потока
    bool								m_bAbort;       //!< Флаг выхода из потока
    QMutex                              m_Mutex;        //!< Мьютекс для синхронизации
    QWaitCondition                      m_RunCondition; //!< Синхронизация
    //boost::posix_time::time_duration	m_SleepTime;

public:
    CThreadImpl();
    virtual ~CThreadImpl();

    //! Создать поток и запустить на исполнение
    void Start();

    //! Завершить корректно исполнение потока
    virtual void Stop();

	//! Get thread running state
	bool IsRunning() const;

    //! Приостановить поток
    void Suspend();

    //! Возобновить поток
    void Resume();

protected:
    //! Реализация бесконечного цикла
    void virtual run();

    //! Вызов функции перед бесконечным циклом
    virtual void PrepareWork()
    {
        // В общей реализации оставляем пустым
    }

    //! Тело потока
    virtual void DoWork()
    {
        // В общей реализации оставляем пустым
    }

	//! Вызов функции при завершении потока
	virtual void DoOnStop()
	{
		// В общей реализации оставляем пустым
	}

private:
    //! Разблокировка и завершение потока
    void Release(bool bAbort = false);
};

#endif // BOOSTTHREADIMPL_H
