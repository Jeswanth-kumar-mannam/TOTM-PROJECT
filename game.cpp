#include "stdafx.h"
#include "game.h"

void game::InitFonts()
{
	m_context->m_assets->add_font(asset_holder::fonts::DOSIS_EXTRALIGHT,"Fonts/Dosis-ExtraLight.otf" );
	m_context->m_assets->add_font(asset_holder::fonts::DOSIS_LIGHT, "Fonts/Dosis-Light.otf");
	m_context->m_assets->add_font(asset_holder::fonts::DOSIS_REGULAR, "Fonts/Dosis-Regular.otf");
	m_context->m_assets->add_font(asset_holder::fonts::DOSIS_MEDIUM,"Fonts/Dosis-Medium.otf" );
	m_context->m_assets->add_font(asset_holder::fonts::DOSIS_SEMIBOLD,"Fonts/Dosis-SemiBold.otf" );
	m_context->m_assets->add_font(asset_holder::fonts::DOSIS_BOLD,"Fonts/Dosis-Bold.otf" );
	m_context->m_assets->add_font(asset_holder::fonts::DOSIS_EXTRABOLD,"Fonts/Dosis-ExtraBold.otf" );
}

void game::InitTextures()
{
	m_context->m_assets->add_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::SPRING, "Images/spring.png");
	m_context->m_assets->add_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::TELEPORTER, "Images/teleporter.png");
	m_context->m_assets->add_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::PLAYER, "Images/player.png");
	m_context->m_assets->add_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::PUFFERFISH, "Images/pufferfish.png");
	m_context->m_assets->add_texture(asset_holder::group_member_name::GANESH, asset_holder::ganesh_textures::BULLET, "Images/bullet.png");
	m_context->m_assets->add_texture(asset_holder::group_member_name::GANESH, asset_holder::ganesh_textures::GUN_CRAB, "Images/Sprite.png");
	m_context->m_assets->add_texture(asset_holder::group_member_name::GANESH, asset_holder::ganesh_textures::DRAGON, "Images/Dragon.png");
}
void game::InitSounds() {
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS,asset_holder::ojjas_sounds::BUTTON_FORWARD, "Sounds/button_forward.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS,asset_holder::ojjas_sounds::BUTTON_BACKWARD, "Sounds/button_backward.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS,asset_holder::ojjas_sounds::BEEP, "Sounds/beep.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BOUNCE, "Sounds/bounce.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::TELEPORT, "Sounds/teleport.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::COLLIDE, "Sounds/collide.wav");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::DEATH, "Sounds/death.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::VICTORY, "Sounds/victory.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::STRETCH, "Sounds/stretch.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::FIRE_START, "Sounds/fireStart.wav");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::FIRE_END, "Sounds/fireEnd.wav");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::BIRD1, "Sounds/BIRD1.wav");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::BIRD2, "Sounds/BIRD2.wav");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::BIRD_NIGHT, "Sounds/BIRD_NIGHT.wav");
}
game::game()

{
	m_context = std::make_shared<context>();
	Data::read(*m_context->m_data.get());
	m_context->m_window->create(sf::VideoMode(30*(int)PLAYER_BASE_SIZE,20*(int)PLAYER_BASE_SIZE), "TOTM Color game", sf::Style::Close);
	InitTextures();
	InitFonts();
	InitSounds();
	m_context->m_states->Add(std::make_unique<main_menu>(m_context));
	// Should only call main menu state,to be done
}

game::~game()
{
}

void game::run()
{
	sf::Clock timer;
	float dt;
	m_context->m_states->ProcessStatechange();
	while ((m_context->m_window->isOpen()) && !(m_context->m_states->is_empty()))
	{
		dt = timer.restart().asSeconds();
		m_context->m_assets->clear_sounds();
		m_context->m_states->Getcurrent()->pollevents();
		m_context->m_states->Getcurrent()->update(dt);
		m_context->m_states->Getcurrent()->render();
		m_context->m_states->ProcessStatechange();

	}
}
