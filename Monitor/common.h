#ifndef		__COMMON_H__
#define		__COMMON_H__

typedef struct ST_DATA
{
	CString		sTime;
	CString		sTemperature;
	CString		sHumidity;

	ST_DATA()
	{
		sTime = _T("");
		sTemperature = _T("");
		sHumidity = _T("");
	}
	const ST_DATA& operator=(const ST_DATA& data)
	{
		sTime = data.sTime;
		sTemperature = data.sTemperature;
		sHumidity = data.sHumidity;
		return *this;
	}

	BOOL operator==(const ST_DATA& data) const
	{
		return ((sTime == data.sTime) && (sTemperature == data.sTemperature) && (sHumidity == data.sHumidity));
	}
}st_data;



#endif