#ifndef ASSET_HOLDER_H
#define ASSET_HOLDER_H

class asset_holder
{
public:

	////////////////////////////////////////////////////////////
	/// \brief enum class to indicate ownership of assets
	///
	////////////////////////////////////////////////////////////
	enum class group_member_name { ADIL, GANESH, MANNAM, OJJAS };

	enum ojjas_sounds { BUTTON_FORWARD, BUTTON_BACKWARD, BEEP, BOUNCE, TELEPORT,COLLIDE,DEATH,VICTORY,STRETCH };
	enum ojjas_textures { SPRING, TELEPORTER,PLAYER,PUFFERFISH };

	enum ganesh_sounds { BIRD1, BIRD2, BIRD_NIGHT, FIRE_START, FIRE_END };
	enum ganesh_textures {BULLET,GUN_CRAB,DRAGON};

	enum fonts {DOSIS_EXTRALIGHT,DOSIS_LIGHT,DOSIS_REGULAR,DOSIS_MEDIUM,DOSIS_SEMIBOLD,DOSIS_BOLD,DOSIS_EXTRABOLD};

	////////////////////////////////////////////////////////////
	/// \brief constructor
	///
	////////////////////////////////////////////////////////////
	

	asset_holder();

	////////////////////////////////////////////////////////////
	/// \brief destructor
	///
	////////////////////////////////////////////////////////////
	~asset_holder();

	////////////////////////////////////////////////////////////
	/// \brief adds texture to assets
	///
	/// \param _name group_member_name name of owner
	/// \param _id int unique id of owner's texture
	/// \param filepath const std::string& path to file where texture present 
	/// \param setrepeated bool decides whether texture can be repeated
	///
	////////////////////////////////////////////////////////////
	void add_texture(group_member_name _name,int id, const std::string& filepath, bool setrepeated = false);

	////////////////////////////////////////////////////////////
	/// \brief adds font to assets
	///
	/// \param _id int unique id of font
	/// \param filepath const std::string& path to file where font present 
	///
	////////////////////////////////////////////////////////////
	void add_font(int id, const std::string& filepath);

	////////////////////////////////////////////////////////////
	/// \brief adds sound buffer to assets
	///
	/// \param _name group_member_name name of owner 
	/// \param _id int unique id of owner's sound buffer
	/// \param filepath const std::string& path to file where sound buffer present 
	///
	////////////////////////////////////////////////////////////
	void add_sound_buffer(group_member_name _name, int id, const std::string& filepath);
	
	////////////////////////////////////////////////////////////
	/// \brief deletes sf::sound objects which are
	/// finished playing
	///
	////////////////////////////////////////////////////////////
	void clear_sounds();

	////////////////////////////////////////////////////////////
	/// \brief plays a sound 
	///
	/// \param _name group_member_name name of owner
	/// \param id int unique id of owner's texture
	/// \param volume float sets the volume of sound value should be
	/// in between 0 and 100
	///
	/// takes key to a sound buffer already present and
	/// creates a sf::sound object which uses it and plays the 
	/// sound object 
	///
	////////////////////////////////////////////////////////////
	void play_sound(group_member_name _name, int id, float volume = 100.f);

	////////////////////////////////////////////////////////////
	/// \brief gets specified texture
	///
	/// \param _name group_member_name name of owner
	/// \param id int unique id of owner's texture
	///
	/// \return lvalue reference to given texture
	///
	////////////////////////////////////////////////////////////
    sf::Texture& get_texture(group_member_name _name, int id)  ;

	////////////////////////////////////////////////////////////
	/// \brief gets specified texture
	///
	/// \param id int unique id of font
	///
	/// \return lvalue reference to given font
	///
	////////////////////////////////////////////////////////////
	sf::Font& get_font(int id);

	////////////////////////////////////////////////////////////
	/// \brief gets specified soundbuffer
	///
	/// \param _name group_member_name name of owner
	/// \param id int unique id of owner's soundbuffer
	///
	/// \return lvalue reference to given soundbuffer
	///
	////////////////////////////////////////////////////////////
	sf::SoundBuffer& get_soundbuffer(group_member_name _name, int id);

private:
	////////////////////////////////////////////////////////////
	/// \brief list of sounds 
	///
	////////////////////////////////////////////////////////////
	std::list<sf::Sound> m_sounds;

	////////////////////////////////////////////////////////////
	/// \brief map of textures 
	///
	/// map which takes a pair containing name of owner 
	/// and id assigned to texture by owner as key and maps it 
	/// to unique ptr of sf::Texture type
	///
	////////////////////////////////////////////////////////////
	std::map<std::pair<group_member_name,int>, std::unique_ptr<sf::Texture>> m_textures;

	////////////////////////////////////////////////////////////
	/// \brief map of fonts
	///
	/// map which takes a id assigned to font key and
	/// maps it to unique ptr of sf::Font type
	///
	////////////////////////////////////////////////////////////
	std::map<int, std::unique_ptr<sf::Font>> m_fonts;

	////////////////////////////////////////////////////////////
	/// \brief map of soundbuffers 
	/// 
	/// map which takes a pair containing name of owner 
	/// and id assigned to soundbuffer by owner as key and maps it 
	/// to unique ptr of sf::SoundBuffer type
	///
	////////////////////////////////////////////////////////////
	std::map<std::pair<group_member_name, int>, std::unique_ptr<sf::SoundBuffer>> m_soundbuffers; 

	////////////////////////////////////////////////////////////
	/// \struct
	/// \brief cotains () operator to be used as predicate
	/// to use remove_if statement with list of sounds
	////////////////////////////////////////////////////////////
	struct is_finished {
		bool operator() (const sf::Sound& value) {
			if (value.getStatus() == sf::SoundSource::Status::Playing) { return false; }
			return true;
		}
	};
};

////////////////////////////////////////////////////////////
/// 
/// \class asset_holder
///
/// \brief class for the asset manager
///
/// This class mantains all assets in the game such as fonts
/// images and sounds,allows for their addition and access
/// and also methods for playing sounds and clearing unnecessary
/// sf::sound objects to mantain the less than 256 sounds 
/// limitation of sfml
///
////////////////////////////////////////////////////////////
#endif
