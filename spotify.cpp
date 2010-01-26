#include "gspot.h"

CSpotify *spotify = new CSpotify();
extern pthread_t mainthread;

/*
 * Spotify session callbacks
 */
sp_session_callbacks cbs;

void
logged_in(sp_session *session, sp_error error)
{
	printf("logged in!\n");
	if(error == SP_ERROR_OK)
		spotify->SetLogin(true);
	else
		spotify->SetLogin(false);
}

void
logged_out(sp_session *session)
{
	printf("logged out!\n");
	spotify->SetLogin(false);
}

void
metadata_updated(sp_session *session)
{

}

void
connection_error(sp_session *session, sp_error error)
{
	printf("connerror.\n");
}

void
message_to_user(sp_session *session, const char* message)
{
	printf("msg: %s\n", message);
}

void
notify_main_thread(sp_session *session)
{
	pthread_kill(mainthread, SIGIO);
}

int
music_delivery(sp_session *session, const sp_audioformat *format, const void *frames, int num_frames)
{
	return 1;
}

void
play_token_lost(sp_session *session)
{

}

void
log_message(sp_session *session, const char* data)
{
	printf("log: %s", data);
}

void
end_of_track(sp_session *session)
{

}

void
init_callbacks()
{
	memset(&cbs, 0, sizeof(sp_session_callbacks));
	cbs.logged_in = &logged_in;
	cbs.logged_out = &logged_out;
	cbs.metadata_updated = &metadata_updated;
	cbs.connection_error = &connection_error;
	cbs.message_to_user = &message_to_user;
	cbs.notify_main_thread = &notify_main_thread;
	cbs.music_delivery = &music_delivery;
	cbs.play_token_lost = &play_token_lost;
	cbs.log_message = &log_message;
	cbs.end_of_track = &end_of_track;
}
/*
 * End of callbacks
 */

CSpotify::CSpotify()
{
	init_callbacks();

	_validSession = false;

	_config.callbacks = &cbs;
	_config.api_version = SPOTIFY_API_VERSION;
	_config.application_key = appkey;
	_config.application_key_size = appkey_size;
	_config.user_agent = "gspot";

	std::string dir = getenv("HOME");
	dir.append("/.gspot/libspotify");

	_config.settings_location = dir.c_str();
	_config.cache_location = dir.c_str();
}

CSpotify::~CSpotify()
{
	Logout();
}

bool
CSpotify::InitSession()
{
	_error = sp_session_init(&_config, &_session);
	if(_error != SP_ERROR_OK) {
		fprintf(stderr, "Could not create a spotify session: %s\n", sp_error_message(_error));
		_validSession = false;
		return false;
	}
	_validSession = true;
	return true;
}

void
CSpotify::SetCredentials(const std::string& username, const std::string& password)
{
	if(username.empty() || password.empty())
		return;

	_user = username;
	_pass = password;
}

void
CSpotify::Login()
{
	if(!isValidSession())
		return;
	if(_user.empty() || _pass.empty())
		return;

	_error = sp_session_login(_session, _user.c_str(), _pass.c_str());

	if(_error != SP_ERROR_OK)
		fprintf(stderr, "Failed to login: %s\n", sp_error_message(_error));
}

void
CSpotify::Logout()
{
	if(!isValidSession() || !isLoggedIn())
		return;
	
	_error = sp_session_logout(_session);
	if(_error != SP_ERROR_OK)
		fprintf(stderr, "Could not log out from Spotify: %s\n", sp_error_message(_error));
}

void
CSpotify::ProcessEvents(int* timeout)
{
	sp_session_process_events(_session, timeout);
}
