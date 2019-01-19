/*
 * Copyright (C) 2016-2018 Radek Malcic
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _Rajce_Rajce_h
#define _Rajce_Rajce_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <Rajce/Rajce.lay>
#include <CtrlCore/lay.h>

#define TFILE <Rajce/Rajce.t>
#include <Core/t.h>

#define IMAGECLASS RajceImg
#define IMAGEFILE  <Rajce/Rajce.iml>
#include <Draw/iml.h>

#define ERR_NO_ERROR  0
#define ERR_NO_DATA  -1
#define ERR_OPEN     -2
#define ERR_CLOSE    -3
#define ERR_READ     -4
#define ERR_CREATE   -5
#define ERR_EXIST    -6
#define ERR_SAVE     -7
#define ERR_SELECT   -8
#define ERR_PARSE    -9
#define ERR_DOWNLOAD -10

struct UserData {
	String url;
	String user;
	bool authorization;
	void Jsonize(JsonIO &jio) { jio("url", url)("user", user)("authorization", authorization); }
	void Xmlize(XmlIO& xio)   { XmlizeByJsonize(xio, *this); }
};

struct QueueData {
	String download_url;
	String download_dir;
	String download_name;
	String album_server_dir;
};

class Rajce:public WithRajceLayout < TopWindow > {
 public:
	typedef Rajce CLASSNAME;
	Rajce();
    virtual ~Rajce() {};

 private:
	String cfg_download_dir;
	String cfg_album_url;
	String cfg_album_user;
	bool   cfg_download_new_only;
	bool   cfg_download_video;
	bool   cfg_append_user_name;
	bool   cfg_enable_user_auth;
	bool   cfg_use_https;
	bool   cfg_use_https_proxy;
	String cfg_https_proxy_url;
	String cfg_https_proxy_port;
	int    cfg_http_timeout_req;
	int    cfg_http_timeout_con;

	String version;
	String internal_name;
	String title_name;
	String download_str;
	bool   init_done;

	Size start_sz;
	Size proxy_sz;

	Array<UserData> userdata;
	Array<QueueData> q;

	FrameRight<Button> del;

	HttpRequest file_http;
	FileOut		file_http_out;
	String		file_http_out_string;
	int64		file_http_loaded;

	HttpRequest http;
	FileOut		http_file_out;        // download directory with filename
	String		http_file_out_string; // download directory with filename
	bool		http_started;
	int			current_lang;

	void SelectDownloadDir(void);
	void Exit(void);

	int  UserDataFind(const String& url);
	void UserDataLoad(void);
	void UserDataAdd(void);
	void UserDataDel(const String& url);
	void UserDataSet(void);
	void UserDataSelect(const String& url);

	void AlbumUrlAdd(const String url);
	void AlbumUrlDel(void);

	void HttpContent(const void *ptr, int size);
	void HttpStart(void);
	bool HttpProxy(void);
	void HttpAuthorization(void);
	bool HttpCheckUrl(void);
	void HttpPrependProtocol(void);
	void HttpAbort(bool ask);
	void HttpDownload(void);
	int  HttpDownloadPage(String url);

	String HttpGetParameterValue(const String param, const String &txt);
	int  HttpParse(void);

	void FileDownload(void);
	void FileContent(const void *ptr, int size);
	void FileProgress(void);
	void FileStart(void);

	void InitText(void);
	void ToggleProxy(void);
	void ToggleAuthorization(void);
	void ToggleDownload(void);
	void ToggleLang(void);
	void ToggleProtocol(void);
	void ToggleTimeoutReq(void);
	void ToggleTimeoutCon(void);
	void ToggleUserDataSelect(void);

	void HttpProxyShow(bool show);
	void EnableElements(bool enable);

	void LoadCfg(void);
	void SaveCfg(void);
	String GetAppDirectory(void);
	String GetCfgFileName(void);
};

#endif

// vim: ts=4
