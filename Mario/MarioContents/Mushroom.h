#pragma once
#include "ItemUnit.h"

// ���� :
class AMushroom : public AItemUnit
{
public:
	// constrcuter destructer
	AMushroom();
	~AMushroom();

	// delete Function
	AMushroom(const AMushroom& _Other) = delete;
	AMushroom(AMushroom&& _Other) noexcept = delete;
	AMushroom& operator=(const AMushroom& _Other) = delete;
	AMushroom& operator=(AMushroom&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void MoveStart() override;
	void FirstInit(float _DeltaTime) override;
	void Appear(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	void CollisionCheck() override;
	void GetHitStart() override;

private:

};

