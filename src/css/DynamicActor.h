
#pragma once

class DynamicActor : public Actor
{
private:
	
	Vector size;		// half size, positive
	Vector bsize;
	Vector vel;
	Vector bvel;
	Vector force;
	
	AABB aabbCurrent;
	
	float mass;
	
	Contact contact;
	
	bool collideUp;
	bool collideSide;
	bool collideDown;
	
public:
	
	//virtual void SetByTemplate( const Actor * src ) override;
	
	virtual void DrawDebug() const override;
	virtual void Draw() const override;
	
	virtual AABB GetAABB() const override;
	virtual float GetHeight() const override;
	
	virtual void Update( const float deltaTime ) override;
	virtual void IdentityCollisionData() override;
	
	virtual void AddForce( const Vector src ) override;
	virtual void AddVelocity( const Vector src ) override;
	virtual void AddPos( const Vector src ) override;
	virtual void Resize( const Vector src ) override;				// full size
	virtual void Rotatate( const Vector src ) override;
	
	virtual void SetForce( const Vector src ) override;
	virtual void SetVelocity( const Vector src ) override;
	virtual void SetPos( const Vector src ) override;
	virtual void SetRotation( const Vector src ) override;
	
	virtual Vector GetForce() const override;
	virtual Vector GetVelocity() const override;
	virtual Vector GetPos() const override;
	virtual Vector GetSize() const override;			// full size
	virtual Vector GetRotation() const override;
	
	
	//virtual void UpdateBinary( const char * binary, const int len ) override;	// includes name and type (class)
	//virtual int GetBinary( char * binary ) const override;		// includes name and type (class), paste binary data in this pointer
	//virtual int GetBinaryLength() const override;				// includes name, type (class),
	
	virtual bool GetRayTrace( const Vector beg, const Vector end, Vector & point, Vector & normal ) override;
	
	
	virtual void Destroy() override;
	
	
	DynamicActor();
	virtual ~DynamicActor() override;
};



