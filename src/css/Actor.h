
#pragma once

class Actor
{
protected:
	
	World * world;
	std::string name;
	
	Vector pos;		// barycenter
	Vector bpos;
	
	GraphicBodyInstance graphicBodyInfo;
	
	bool queueToDestroy;
	
	void * customData;		// this can use gameDeveloper, he must constract and destruct it on his own
	
public:
	
	void ** GetCustomData();
	
	World * GetWorld() const;
	
	virtual void Set( const Actor * src );
	
	virtual void Draw() const=0;
	virtual void DrawDebug() const=0;
	
	virtual void SetBySameType( Actor * src )=0;
	
	virtual Vector GetPhysicsAABB() const=0;
	virtual Vector GetGraphicAABB() const=0;
	virtual float GetHeight() const=0;
	
	virtual Vector GetForwardVector() const=0;
	virtual Vector GetRightVector() const =0;
	virtual Vector GetUpVector() const=0;
	
	virtual void Update( const float deltaTime )=0;
	
	virtual void AddForce( const Vector src )=0;
	virtual void AddVelocity( const Vector src )=0;
	virtual void AddPos( const Vector src )=0;
	virtual void AddSize( const Vector src )=0;				// half size
	virtual void AddRotation const Vector src )=0;
	
	virtual void SetForce( const Vector src )=0;
	virtual void SetVelocity( const Vector src )=0;
	virtual void SetPos( const Vector src )=0;
	virtual void SetSize( const Vector src )=0;				// half size
	virtual void SetRotation( const Vector src )=0;
	
	virtual Vector GetForce() const=0;
	virtual Vector GetVelocity() const=0;
	virtual Vector GetPos() const=0;
	virtual Vector GetSize() const=0;			// half size
	virtual Vector GetRotation() const=0;
	
	
	virtual int GetBinaryLength() const=0;				// includes name, type (class),
	virtual int GetBinary( char * binary ) const=0;		// includes name and type (class), paste binary data in this pointer
	virtual void SetBinary( const char * binary, const int len )=0;	// includes name and type (class)
	
	
	static void IsBinaryTriggerVolumeActor( const char * binary, const int len );
	static void IsBinaryDynamicActor( const char * binary, const int len );
	static void IsBinaryStaticActor( const char * binary, const int len );
	
	static Actor * GetNewActorTemplateByBinary( const char * binary, const int len );
	static Actor * GetNewActorByBinary( const char * binary, const int len );
	
	static Actor * GetNewActorByTemplate( const Actor * src );
	
	static void Destroy( Actor * src );
	virtual void Destroy()=0;
	void QueueToDestroy()=0;
	
	Actor();
	~Actor();
};



