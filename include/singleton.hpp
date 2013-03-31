//30.03.2013
//v0.1


#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
	public:
		static T* getInstance()
		{
			if(_singleton == nullptr)
				_singleton = new T;
				
			return _singleton;
		}
		
		static void kill()
		{
			if(_singleton != nullptr)
				delete _singleton;
		}
	
	protected:
		Singleton(){}
		Singleton(Singleton const&){}
		Singleton & operator=(Singleton const&){}
		~Singleton(){}
		
	private:	
		static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = nullptr;

#endif //SINGLETON_H
