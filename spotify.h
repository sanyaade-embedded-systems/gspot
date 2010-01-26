#ifndef _SPOTIFY_H
#define _SPOTIFY_H

class CSpotify
{
	public:
		CSpotify();
		~CSpotify();
		bool InitSession();
		void SetCredentials(const std::string& username, const std::string& password);
		void Login();
		void Logout();
		void ProcessEvents(int* timeout);

		void SetLogin(bool state) { _loggedIn = (state == true); }

		bool isValidSession() { return _validSession == true; }
		bool isLoggedIn() { return _loggedIn == true; }
	private:
		sp_session_config _config;
		sp_session *_session;
		sp_error _error;
		bool _validSession, _loggedIn;
		std::string _user, _pass;
};

extern CSpotify *spotify;

#endif
