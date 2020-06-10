#ifndef		__SINGLETON_H__
#define		__SINGLETON_H__

template <typename T>
class Singleton
{
private:
	Singleton() {}
	Singleton(const Singleton& rhs);
	Singleton& operator=(const Singleton& rhs);

public:
	static T * Instance()
	{
		static T * pT = NULL;
		if (!pT)
		{
			static T instance;
			pT = &instance;
		} 
		return pT;
	}
};

#endif // __SINGLETON_H__
