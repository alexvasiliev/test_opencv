#ifndef THREAD_HPP
#define THREAD_HPP

#include <list>
#include <map>
#include <QSharedPointer>

//! Интерфейс для потока
class IThread
{
public:
    virtual ~IThread() {}

    //! Запустить поток на исполнение
    virtual void Start() = 0;

    //! Завершить корректно исполнение потока
    virtual void Stop() = 0;

	//! Get thread running state
	virtual bool IsRunning() const = 0;

    //! Приостановить поток
    virtual void Suspend() = 0;

    //! Возобновить поток
    virtual void Resume() = 0;

protected:
    //! Тело потока
    virtual void DoWork() = 0;
};

//! Умный указатель на объект потока
typedef QSharedPointer<IThread>  PThread;


#endif // THREAD_HPP
