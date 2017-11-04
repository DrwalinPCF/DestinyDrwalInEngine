


/////////////////////
// End playing sound:
class MySoundEndReceiver : public irrklang::ISoundStopEventReceiver
{
public:
	virtual void OnSoundStopped( irrklang::ISound * sound, irrklang::E_STOP_EVENT_CAUSE reason, void * userData )
	{
		sound -> drop();
		return;
	}
};
MySoundEndReceiver* myGlobalReceiver = new MySoundEndReceiver();



//////////////////
// Sample Methods:

SoundEngine::SoundSource::SoundSource()
{
	source = NULL;
}

SoundEngine::SoundSource::~SoundSource()
{
	if( source != NULL )
		source->drop();
}



////////////////////////
// Sound Engine Methods:

inline void SoundEngine::Init()
{
	SEngine = irrklang::createIrrKlangDevice();
}

inline void SoundEngine::DeInit()
{
	if( SEngine != NULL )
		SEngine->drop();
	samples.resize( 0 );
}

inline void SoundEngine::Update()
{
	Vector pos;
	pos = engineInstance->Object(0)->GetEyePos();
	
	VMatrix matrix;
	
	matrix.InitEmpty();
	matrix.RotateY( engineInstance->Object(0)->see[0]-90.0f );
	matrix.RotateX( -engineInstance->Object(0)->see[1] );
	Vector look = matrix.GetVertex( SetVector( 0.0f, 0.0f, 1000.0f ) );
	Vector up = matrix.GetVertex( SetVector( 0.0f, 1000.0f, 0.0f ) );
	
	irrklang::vec3df position( pos[0], pos[1], pos[2] );			// position of the listener
	irrklang::vec3df lookDirection( look[0], look[1], look[2] );	// the direction the listener looks into
	irrklang::vec3df velPerSecond(0,0,0);							// only relevant for doppler effects
	irrklang::vec3df upVector( up[0], up[1], up[2] );				// where 'up' is in your 3D scene
	
	SEngine->setListenerPosition( position, lookDirection, velPerSecond, upVector );
}

inline void SoundEngine::AddSound( char * src )
{
	ifstream file;
	file.open( src );
	if( file.good() )
	{
		soundSource[src].source = SEngine->addSoundSourceFromFile( src );
	}
}

inline void SoundEngine::PlaySound( const char * src, float volume )
{
	it auto = soundSource.find(src);
	if( it != soundSource.end() )
	{
		irrklang::ISound * snd_ = SEngine->play2D( it->second.source, false, false, true );
		snd_ -> setSoundStopEventReceiver(myGlobalReceiver);
		snd_ -> setVolume( volume * GlobalVolume );
		snd_ = NULL;
	}
}

inline void SoundEngine::PlaySound( const char * src, Vector origin )
{
	PlaySound( src, origin, 1.13f );
}

inline void SoundEngine::PlaySound( const char * src, Vector origin, float minDistance )
{
	it auto = soundSource.find(src);
	if( it != soundSource.end() )
	{
		irrklang::ISound * snd_ = NULL;
		irrklang::vec3df position( origin[0], origin[1], origin[2] );
		
		snd_ = SEngine->play3D( it->second.source, position, false, false, true, false );
		snd_ -> setSoundStopEventReceiver(myGlobalReceiver);
		snd_ -> setMinDistance( minDistance );
		snd_ -> setVolume( GlobalVolume );
		snd_ = NULL;
	}
}

inline void SoundEngine::SetVolume( float dst )
{
	GlobalVolume = dst;
}

inline float SoundEngine::GetVolume()
{
	return GlobalVolume;
}

SoundEngine::SoundEngine()
{
	GlobalVolume = 1.0f;
	SEngine = NULL;
}

SoundEngine::~SoundEngine()
{
	GlobalVolume = 0.0f;
	DeInit();
}


