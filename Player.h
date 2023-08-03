#pragma once
#include "Object.h"

enum class PlayerType
{
	CanonTank,
	MissileTank,
};

class Player : public Object
{
public:
	Player();
	virtual		 ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	wstring		 GetMeshKey();
	void		 SetPlayerType(PlayerType type) { _playerType = type; }
	void		 SetPlayerId(int32 playerId) { _playerId = playerId; }
	void		 SetPlayerTurn(bool playerTurn) { _playerTurn = playerTurn; }
	void		 SetShoted(bool shoted) { _shoted = shoted; }

	int32		 GetPlayerId() { return _playerId; }
	PlayerType	 GetPlayerType() { return _playerType; }
	bool		 GetPlayerTurn() { return _playerTurn; }
	bool		 GetShoted() { return _shoted; }
	void		 UpdateFireAngle();

public:
	int32		 _playerId = 0;
	PlayerType	 _playerType = PlayerType::CanonTank;
	bool		 _playerTurn = false;
	bool		 _shoted = false;
	float		 _fireAngle = 0.f;
};

