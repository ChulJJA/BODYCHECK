#include "Message_Function_Respawn.h"
#include "Referee.h"
#include "Engine.hpp"
#include "Message.h"

void Msg_Func_Respawn::Init()
{
}

void Msg_Func_Respawn::Update(float dt)
{

	if (m_from->GetName() == "second")
	{
		sound.Play(SOUND::Die);
		Referee::Get_Referee()->Get_Stage_Statement().push_back(Referee::PLAYER_SECOND_DIE);
	}
	if (m_from->GetName() == "first")
	{
		sound.Play(SOUND::Die);

		Referee::Get_Referee()->Get_Stage_Statement().push_back(Referee::PLAYER_FIRST_DIE);
	}
	if (m_from->GetName() == "third")
	{
		sound.Play(SOUND::Die);

		Referee::Get_Referee()->Get_Stage_Statement().push_back(Referee::PLAYER_THIRD_DIE);
	}
	if (m_from->GetName() == "forth")
	{
		sound.Play(SOUND::Die);

		Referee::Get_Referee()->Get_Stage_Statement().push_back(Referee::PLAYER_FOURTH_DIE);
	}

	msg->Set_Should_Delete(true);
}
