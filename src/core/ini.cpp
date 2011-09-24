/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: ini file
*/


#include "hge_impl.h"

void CALL HGE_Impl::Ini_SetInt(const char *section, const char *name, int value, char * inifilename/* =NULL */)
{
	char buf[256];

	char * filename = inifilename;
	if (!filename)
	{
		filename = szIniFile;
	}
	else
	{
		filename = Resource_MakePath(filename);
	}

	if(filename[0]) {
		sprintf(buf,"%d",value);
		_IniWritePrivateProfileString(section, name, buf, filename);
	}
}


int CALL HGE_Impl::Ini_GetInt(const char *section, const char *name, int def_val, char * inifilename/* =NULL */)
{
	char buf[256];

	char * filename = inifilename;
	if (!filename)
	{
		filename = szIniFile;
	}
	else
	{
		filename = Resource_MakePath(filename);
	}

	if(filename[0]) {
		if(_IniGetPrivateProfileString(section, name, "", buf, sizeof(buf), filename))
		{ return Math_atoi(buf); }
		else { return def_val; }
	}
	return def_val;
}


void CALL HGE_Impl::Ini_SetFloat(const char *section, const char *name, float value, char * inifilename/* =NULL */)
{
	char buf[256];

	char * filename = inifilename;
	if (!filename)
	{
		filename = szIniFile;
	}
	else
	{
		filename = Resource_MakePath(filename);
	}

	if(filename[0]) {
		sprintf(buf,"%f",value);
		_IniWritePrivateProfileString(section, name, buf, filename);
	}
}


float CALL HGE_Impl::Ini_GetFloat(const char *section, const char *name, float def_val, char * inifilename/* =NULL */)
{
	char buf[256];

	char * filename = inifilename;
	if (!filename)
	{
		filename = szIniFile;
	}
	else
	{
		filename = Resource_MakePath(filename);
	}

	if(filename[0]) {
		if(_IniGetPrivateProfileString(section, name, "", buf, sizeof(buf), filename))
		{ return (float)Math_atof(buf); }
		else { return def_val; }
	}
	return def_val;
}


void CALL HGE_Impl::Ini_SetString(const char *section, const char *name, const char *value, char * inifilename/* =NULL */)
{
	char * filename = inifilename;
	if (!filename)
	{
		filename = szIniFile;
	}
	else
	{
		filename = Resource_MakePath(filename);
	}
	if(filename[0]) _IniWritePrivateProfileString(section, name, value, filename);
}


char* CALL HGE_Impl::Ini_GetString(const char *section, const char *name, const char *def_val, char * inifilename/* =NULL */)
{
	char * filename = inifilename;
	if (!filename)
	{
		filename = szIniFile;
	}
	else
	{
		filename = Resource_MakePath(filename);
	}
	if(filename[0]) _IniGetPrivateProfileString(section, name, def_val, szIniString, sizeof(szIniString), filename);
	else strcpy(szIniString, def_val);
	return szIniString;
}

#ifndef __WIN32
#include <list>
using namespace std;
bool _IniStringCut(const char * line, char * prestr, char * poststr)
{
	strcpy(prestr, "");
	strcpy(poststr, "");
	if (!strlen(line))
	{
		return false;
	}

	int ilinebegin = -1;
	int ilineend = 0;
	int i=0;
	for (; i<strlen(line); i++)
	{
		if (!isspace(line[i]))
		{
			if (line[i] == '#' || line[i] == ';')
			{
				return false;
			}
			ilinebegin = i;
			break;
		}
	}
	if (ilinebegin < 0)
	{
		return false;
	}
	strcpy(prestr, &line[ilinebegin]);
	if (!strlen(prestr))
	{
		return false;
	}
	i = strlen(prestr)-1;
	for (; i>=0; i--)
	{
		if (!isspace(prestr[i]))
		{
			ilineend = i+1+ilinebegin;
			prestr[i+1] = 0;
			break;
		}
	}

	i = 0;
	int iequal = 0;
	for (; i<strlen(prestr); i++)
	{
		if (prestr[i] == '=')
		{
			iequal = i;
			break;
		}
	}
	if (!iequal)
	{
		return true;
	}

	i = iequal+1;
	for (; i<strlen(prestr); i++)
	{
		if (!isspace(prestr[i]))
		{
			if (prestr[i] == '\"')
			{
				sscanf(&prestr[i], "\"%[^\"]\"", poststr);
			}
			else if (prestr[i] == '\'')
			{
				sscanf(&prestr[i], "\'%[^\']\'", poststr);
			}
			else
			{
				strcpy(poststr, &prestr[i]);
			}
			break;
		}
	}
	if (!strlen(poststr))
	{
		strcpy(poststr, " ");
	}
	prestr[iequal] = 0;
	i = strlen(prestr)-1;
	for (; i>=0; i--)
	{
		if (!isspace(prestr[i]))
		{
			break;
		}
		prestr[i] = 0;
	}
	if (!strlen(prestr))
	{
		strcpy(prestr, "");
		strcpy(poststr, "");
		return false;
	}
	return true;
}

bool _IniFindAppname(const char * appname, const char * line)
{
	if (!strlen(appname))
	{
		return false;
	}

	char buffer[256];
	char tbuff[256];
	_IniStringCut(line, buffer, tbuff);
	if (!strlen(buffer) || buffer[0] != '[')
	{
		return false;
	}
	sscanf(buffer, "[%[^]]]", tbuff);
	if (!strcmp(tbuff, appname))
	{
		return true;
	}
	return false;
}

bool _IniSetKey(const char * keyname, const char * value, char * line, bool newkey=false)
{
	if (newkey)
	{
		sprintf(line, "%s=%s\n", keyname, value);
		return true;
	}
	char prestr[256];
	char poststr[256];
	if (_IniStringCut(line, prestr, poststr))
	{
		if (!strlen(poststr))
		{
			return false;
		}
		if (strcmp(prestr, keyname))
		{
			return false;
		}
		else
		{
			sprintf(line, "%s=%s\n", keyname, value);
			return true;
		}
	}
	return false;
}

bool _IniCreateAppname(const char * appname, char * line)
{
	sprintf(line, "[%s]\n", appname);
	return true;
}

typedef struct tag_IniLine
{
	char line[256];
}_IniLine;

#endif // __WIN32

DWORD HGE_Impl::_IniGetPrivateProfileString(const char * appname, const char * keyname, const char * defval, char * retstr, DWORD size, const char * filename)
{
#ifdef __WIN32
	return GetPrivateProfileString(appname, keyname, defval, retstr, size, filename);
#else

	if (!retstr)
	{
		return 0;
	}
	if (!strlen(appname) || !strlen(keyname))
	{
		strcpy(retstr, defval);
		return strlen(retstr);
	}
	FILE * file = fopen(filename, "r");
	if (file)
	{
		char line[256];
		char prestr[256];
		char poststr[256];

		bool done = false;
		while (fgets(line, 256, file) != NULL)
		{
			if (_IniStringCut(line, prestr, poststr))
			{
				char tbuff[256];
				sscanf(prestr, "[%[^]]]", tbuff);
				if (strlen(prestr) && !strcmp(tbuff, appname) && !strlen(poststr))
				{
					done = true;
					break;
				}
			}
		}
		if (done)
		{
			while (fgets(line, 256, file) != NULL)
			{
				_IniStringCut(line, prestr, poststr);
				if (!strlen(poststr) && strlen(prestr))
				{
					break;
				}
				if (!strcmp(prestr, keyname))
				{
					strcpy(retstr, poststr);
					fclose(file);
					return strlen(retstr);
				}
			}
		}
		fclose(file);
	}
	strcpy(retstr, defval);
	return strlen(retstr);

#endif // __WIN32
}

bool HGE_Impl::_IniWritePrivateProfileString(const char * appname, const char * keyname, const char * val, const char * filename)
{
#ifdef __WIN32
	return WritePrivateProfileString(appname, keyname, val, filename);
#else

	FILE * file = fopen(filename, "r");
	if (!file)
	{
		file = fopen(filename, "w");
		if (!file)
		{
			return false;
		}
	}

	list<_IniLine> lines;
	fseek(file, 0, SEEK_SET);

	_IniLine _line;
	while (fgets(_line.line, 256, file) != NULL)
	{
		if (!strlen(_line.line))
		{
			continue;
		}
		if (_line.line[strlen(_line.line)-1] != '\n')
		{
			strcat(_line.line, "\n");
		}
		lines.push_back(_line);
	}
	fclose(file);

	bool appfound = false;
	bool done = false;
	list<_IniLine>::iterator it;
	list<_IniLine>::iterator app;
	for (it=lines.begin(); it!=lines.end(); it++)
	{
		if (!appfound)
		{
			if (_IniFindAppname(appname, it->line))
			{
				app = it;
				++app;
				appfound = true;
			}
		}
		else
		{
			if (_IniSetKey(keyname, val, it->line))
			{
				done = true;
				break;
			}
		}
	}
	if (!done)
	{
		_IniLine _tline;
		if (!appfound)
		{
			_IniCreateAppname(appname, _tline.line);
			lines.push_back(_tline);
			app = lines.end();
		}
		_IniSetKey(keyname, val, _tline.line, true);
		lines.insert(app, _tline);
	}

	file = fopen(filename, "w");
	if (!file)
	{
		return false;
	}
	for (list<_IniLine>::iterator it=lines.begin(); it!=lines.end(); it++)
	{
		fwrite(it->line, strlen(it->line), 1, file);
	}
	fclose(file);

	return true;

#endif // __WIN32
}