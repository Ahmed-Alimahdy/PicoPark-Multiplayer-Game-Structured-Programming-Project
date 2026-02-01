#include<SFML/Graphics.hpp>
#include<iostream> 
#include <SFML/Audio.hpp>
#include<string>
#include <fstream>
#define ng1 33
#define ng2 8
#define ng3 22
#define ne1 1
#define ne3 2
using namespace sf;
using namespace std;
//global declaration//
RenderWindow window(VideoMode(1920, 1080), "Pico Park");
Event e;
Font font;
Clock gameclock;
bool type_language = false, beginning = true, edited_music, beginning_intro = 1, level_opened = false, extreme_x = 0, gamecontrol = 1
, back_choose_select = 0, Pass2 = false, Pass3 = false;
int cnt_language = 0, cnt_music = 12, cnt_volume_wasd = 12, ani = 0, a = 0, speed = 4000, x = 0, x2 = 0, y = 0,
cnt_player1 = 0, cnt_player2 = 0, y2 = 0, counter_pages = 1, choose_option = 4, q = 0;
float deltatime = 0, sound_volume = 100, music_Volume = 100, delay = 0.1f, gravity = 5.0, timer3 = 0, delay2 = 0.1f,
deltatime2 = 0, viewdeltax, viewxcalc, timer = 0;
Music music;
string name3, name4, name1, name2;
RectangleShape pinkback;
VertexArray quads(Quads, 4);
CircleShape arrow1(10.f, 3.f), arrow2(10.f, 3.f);
Sprite  Left_icon, Right_icon, Right_icon2, Left_icon2, Text_box, Volume_icon[3] = {}, Music_icon[3] = {}, lvlint, Block1, Block2;
Text  option, edit_sound, edit_music, language, back, choice_english, choice_francais,
F_option, F_sound, F_music, F_language, F_back, lvl, to_main, to_lvlsell, fto_lvlsell, fto_main, name_player1, name_player2;
Time seek_time;
struct PLAYERNEEDS_1 {
	Texture idle[8];
	Texture walk[8];
	Texture jump[8];
	Texture dead[8];
	Texture faceset[8];
	int scale = 0;
	float jumpheight = {}, startposition = {};
};
struct PLAYERNEEDS_2 {
	Texture idle[4];
	Texture walk[4];
	Texture jump[4];
	Texture dead[4];
	Texture faceset[4];
	int scale = 0;
	float jumpheight = {}, startposition = {};
};
struct start {
	Texture startshape;
	Sprite  temp;
	Text    starttext;
	string  levelselected;
};
struct menu {
	Text edit_start, edit_option, edit_exit, credit;
};
struct credit_fun
{
	Texture background, banner, textbox;
	Sprite Background, Banner, Textbox;
	Music music;
	float timer3 = 0;
	Text credit_texts[21];

};
start lvl1, lvl2, lvl3;
void music_handle();
void  embedded_draw_pause();
void turnup_sound(int&, int&);
void turnup_music(int&, int&);
void turndown_sound(int&, int&);
void turndown_music(int&, int&);
void scroll_up(int&);
void scroll_down(int&);
void lang_right(int&);
void lang_left(int&);
void lang_update_anima();
void pause_unpause(bool&);
int back_isselected();
int select_isselected();
int main_isselected();
bool isGrounded_level1(Sprite player, Sprite g[])
{
	bool grounded = 0;
	for (int i = 0; i < ng1; i++)
	{
		if (i == 8)
			continue;
		if (player.getGlobalBounds().intersects(g[i].getGlobalBounds()))
			grounded = 1;
	}
	if (!gamecontrol)
		grounded = 1;
	return grounded;
}
bool isGrounded2_level1(Sprite player, Sprite g[])
{
	bool grounded = 0;
	for (int i = 0; i < ng1; i++)
	{
		if (i == 8)
			continue;
		if (player.getGlobalBounds().intersects(g[i].getGlobalBounds()))
			grounded = 1;
	}
	if (!gamecontrol)
		grounded = 1;
	return grounded;
}
bool isGrounded_level2(Sprite player[], Sprite g[], Sprite Block1, Sprite Block2)
{
	bool grounded = 0;
	for (int i = 0; i < ng2; i++)
	{
		if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
			grounded = 1;
		if (player[x].getGlobalBounds().intersects(Block1.getGlobalBounds()))
			grounded = 1;
		if (player[x].getGlobalBounds().intersects(Block2.getGlobalBounds()))
			grounded = 1;
	}
	if (!gamecontrol)
		grounded = 1;

	return grounded;
}
bool isGrounded2_level2(Sprite player[], Sprite g[], Sprite Block1, Sprite Block2)
{
	bool grounded = 0;
	for (int i = 0; i < ng2; i++)
	{
		if (player[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()))
			grounded = 1;
		if (player[x2].getGlobalBounds().intersects(Block1.getGlobalBounds()))
			grounded = 1;
		if (player[x2].getGlobalBounds().intersects(Block2.getGlobalBounds()))
			grounded = 1;
	}
	if (!gamecontrol)
		grounded = 1;
	return grounded;
}
bool isGrounded_level3(Sprite player, Sprite g[], Sprite e[])
{
	bool grounded = 0;
	for (int i = 0; i < ng3; i++)
	{

		if (player.getGlobalBounds().intersects(g[i].getGlobalBounds()))
			grounded = 1;
	}
	for (int i = 0; i < ne3; i++)
	{
		if (player.getGlobalBounds().intersects(e[i].getGlobalBounds()))
			grounded = 1;
	}
	if (!gamecontrol)
		grounded = 1;
	return grounded;
}
bool isGrounded2_level3(Sprite player, Sprite g[], Sprite e[])
{
	bool grounded = 0;
	for (int i = 0; i < ng3; i++)
	{
		if (player.getGlobalBounds().intersects(g[i].getGlobalBounds()))
			grounded = 1;
	}
	for (int i = 0; i < ne3; i++)
	{

		if (player.getGlobalBounds().intersects(e[i].getGlobalBounds()))
			grounded = 1;
	}
	if (!gamecontrol)
		grounded = 1;
	return grounded;
}
void option_window(float& sound_volume, float& music_Volume);
void game_intro();
void choose_player_window(bool a, float music_Volume, int& x, int& x2);
void level_select(bool a, float music_Volume, string& name1, string& name2);
void main_menu();
void level3();
void level1();
void level2();
void  lvl1_intro(float wid, float hei);
void  lvl2_intro(float wid, float hei);
void  lvl3_intro(float wid, float hei);
void  embeddeddraw_intro_lvl1();
void  embeddeddraw_intro_lvl2();
void  embeddeddraw_intro_lvl3();
void credit();
int main()
{
	/*if (beginning_intro)
	{
		game_intro();
	}
	music.openFromFile("./NinjaAdventure/Musics/22 - Dream.ogg");
	music.setLoop(true);
	music.play();
	if (beginning)
	{
		main_menu();
	}
	music.stop();
	music.play();
	music.setVolume(music_Volume);
	option_window(sound_volume, music_Volume);*/
	level1();
	return 0;
}
void option_window(float& sound_volume, float& music_Volume)
{
	Texture background, textbox, volume_icon[3], music_icon[3];
	Sprite Background, Textbox, Volume_icon[3], Music_icon[3];
	Text option, edit_sound, edit_music, language, back, choice_english, choice_francais, back_choose_player, F_option, F_sound, F_music, F_language, F_back;
	RectangleShape volume_sound1(Vector2f(13, 22)), volume_sound2(Vector2f(13, 31)), volume_sound3(Vector2f(13, 40)), volume_sound4(Vector2f(13, 49)), volume_sound5(Vector2f(13, 58)), volume_sound6(Vector2f(13, 67)), volume_music1(Vector2f(13, 22)), volume_music2(Vector2f(13, 31)),
		volume_music3(Vector2f(13, 40)), volume_music4(Vector2f(13, 49)), volume_music5(Vector2f(13, 58)), volume_music6(Vector2f(13, 67));
	CircleShape arrow1(12.0, 3), arrow2(12.0, 3);
	int choose_option = 0;
	Music switching;
	Time duration_music;
	//properties of background
	background.loadFromFile("./NinjaAdventure/Backgrounds/Tilesets/TilesetField.png");
	Background.setTextureRect(IntRect(0, 50, 60, 60));
	Background.setTexture(background);
	Background.setPosition(-500, -500);
	Background.setScale(100, 100);
	//properties of music
	switching.openFromFile("./NinjaAdventure/Sounds/Menu/Menu4.wav");
	//properties of texts
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	option.setFont(font);
	option.setString("OPTION");
	option.setFillColor(Color::Red);
	option.setPosition(750, 100);
	option.setCharacterSize(110);
	//--------------------------
	edit_sound.setFont(font);
	edit_sound.setString("SOUND");
	edit_sound.setFillColor(Color::White);
	edit_sound.setOutlineThickness(1);
	edit_sound.setOutlineColor(Color::Black);
	edit_sound.setPosition(730, 320);
	edit_sound.setCharacterSize(50);
	//--------------------------
	edit_music.setFont(font);
	edit_music.setString("MUSIC");
	edit_music.setFillColor(Color::White);
	edit_music.setOutlineThickness(1);
	edit_music.setOutlineColor(Color::Black);
	edit_music.setPosition(730, 500);
	edit_music.setCharacterSize(50);
	//--------------------------
	language.setFont(font);
	language.setString("LANGUAGE");
	language.setFillColor(Color::White);
	language.setOutlineThickness(1);
	language.setOutlineColor(Color::Black);
	language.setPosition(730, 680);
	language.setCharacterSize(50);
	//---------------------------
	back.setFont(font);
	back.setString("BACK");
	back.setFillColor(Color::White);
	back.setOutlineThickness(1);
	back.setOutlineColor(Color::Black);
	back.setPosition(730, 830);
	back.setCharacterSize(50);
	//---------------------------
	choice_english.setFont(font);
	choice_english.setString("ENGLISH");
	choice_english.setFillColor(Color::Transparent);
	choice_english.setPosition(870, 745);
	choice_english.setCharacterSize(50);
	//---------------------------
	choice_francais.setFont(font);
	choice_francais.setString("FRANÇAIS");
	choice_francais.setFillColor(Color::Transparent);
	choice_francais.setPosition(860, 745);
	choice_francais.setCharacterSize(48);
	//---------------------------
	F_option.setFont(font);
	F_option.setString("PRAMÈTRES");
	F_option.setFillColor(Color::Red);
	F_option.setPosition(650, 100);
	F_option.setCharacterSize(110);
	//---------------------------
	F_sound.setFont(font);
	F_sound.setString("SON");
	F_sound.setFillColor(Color::White);
	F_sound.setOutlineThickness(1);
	F_sound.setOutlineColor(Color::Black);
	F_sound.setPosition(730, 320);
	F_sound.setCharacterSize(50);
	//----------------------------
	F_music.setFont(font);
	F_music.setString("MUSIQUE");
	F_music.setFillColor(Color::White);
	F_music.setOutlineThickness(1);
	F_music.setOutlineColor(Color::Black);
	F_music.setPosition(730, 500);
	F_music.setCharacterSize(50);
	//---------------------------
	F_language.setFont(font);
	F_language.setString("LANGUE");
	F_language.setFillColor(Color::White);
	F_language.setOutlineThickness(1);
	F_language.setOutlineColor(Color::Black);
	F_language.setPosition(730, 680);
	F_language.setCharacterSize(50);
	//--------------------------
	F_back.setFont(font);
	F_back.setString("DOS");
	F_back.setFillColor(Color::White);
	F_back.setOutlineThickness(1);
	F_back.setOutlineColor(Color::Black);
	F_back.setPosition(730, 830);
	F_back.setCharacterSize(50);
	//properties of textbox
	textbox.loadFromFile("./NinjaAdventure/HUD/Dialog/DialogueBoxSimple.png");
	Textbox.setTexture(textbox);
	Textbox.setPosition(700, 250);
	Textbox.setScale(2, 12);
	//icons
	volume_icon[0].loadFromFile("./NinjaAdventure/icons/volume-up-interface-symbol.png");
	Volume_icon[0].setTexture(volume_icon[0]);
	Volume_icon[0].setPosition(780, 395);
	Volume_icon[0].setScale(.16f, .16f);
	volume_icon[1].loadFromFile("./NinjaAdventure/icons/volume.png");
	Volume_icon[1].setTexture(volume_icon[1]);
	Volume_icon[1].setPosition(780, 402);
	Volume_icon[1].setScale(.12f, .13f);
	volume_icon[2].loadFromFile("./NinjaAdventure/icons/mute.png");
	Volume_icon[2].setTexture(volume_icon[2]);
	Volume_icon[2].setPosition(770, 404);
	Volume_icon[2].setScale(.12f, .12f);
	//----------------------------
	music_icon[0].loadFromFile("./NinjaAdventure/icons/quaver.png");
	Music_icon[0].setTexture(music_icon[0]);
	Music_icon[0].setPosition(780, 585);
	Music_icon[0].setScale(.15f, .15f);
	music_icon[1].loadFromFile("./NinjaAdventure/icons/music.png");
	Music_icon[1].setTexture(music_icon[1]);
	Music_icon[1].setPosition(785, 590);
	Music_icon[1].setScale(.15f, .15f);
	music_icon[2].loadFromFile("./NinjaAdventure/icons/mute_music.png");
	Music_icon[2].setTexture(music_icon[2]);
	Music_icon[2].setPosition(780, 595);
	Music_icon[2].setScale(.14f, .14f);
	//---------------------------
	volume_sound1.setPosition(940, 445);
	volume_sound1.setFillColor(Color::White);
	volume_sound2.setPosition(960, 436);
	volume_sound2.setFillColor(Color::White);
	volume_sound3.setPosition(980, 427);
	volume_sound3.setFillColor(Color::White);
	volume_sound4.setPosition(1000, 418);
	volume_sound4.setFillColor(Color::White);
	volume_sound5.setPosition(1020, 409);
	volume_sound5.setFillColor(Color::White);
	volume_sound6.setPosition(1040, 400);
	volume_sound6.setFillColor(Color::White);
	//----------------------------
	volume_music1.setPosition(940, 635);
	volume_music1.setFillColor(Color::White);
	volume_music2.setPosition(960, 626);
	volume_music2.setFillColor(Color::White);
	volume_music3.setPosition(980, 617);
	volume_music3.setFillColor(Color::White);
	volume_music4.setPosition(1000, 608);
	volume_music4.setFillColor(Color::White);
	volume_music5.setPosition(1020, 599);
	volume_music5.setFillColor(Color::White);
	volume_music6.setPosition(1040, 590);
	volume_music6.setFillColor(Color::White);
	//---------------------------
	arrow1.setPosition(1190, 765);
	arrow1.setRotation(90);
	arrow1.setFillColor(Color::Black);
	//--------------------------
	arrow2.setPosition(810, 792);
	arrow2.setRotation(270);
	arrow2.setFillColor(Color::Black);
	while (window.isOpen())
	{
		if (music.getStatus() == music.Playing)
			seek_time = music.getPlayingOffset();
		gameclock.restart();
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{

				window.close();
			}
			//switching between option choices
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				choose_option = (choose_option + 1) % 8;
				switching.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				choose_option--;
				if (choose_option < 0)
					choose_option = 7;
				switching.play();
			}
			//turn the sound up and down
			if (choose_option == 0 || choose_option == 7)
			{
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					cnt_volume_wasd = (cnt_volume_wasd + 1) % 14;
					if (cnt_volume_wasd > 11)
						cnt_volume_wasd = 12;

				}
			}
			if (choose_option == 0 || choose_option == 7)
			{
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					cnt_volume_wasd--;
					if (cnt_volume_wasd < 0)
						cnt_volume_wasd = 0;
				}
			}
			//turn the music up and down
			if (choose_option == 2 || choose_option == 1)
			{
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					cnt_music = (cnt_music + 1) % 14;
					if (cnt_music > 11)
						cnt_music = 12;
					beginning = false;
					music_handle();
				}

			}
			if (choose_option == 1 || choose_option == 2)
			{
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					cnt_music--;
					if (cnt_music < 0)
						cnt_music = 0;
					beginning = false;
					music_handle();
				}
			}
			if (choose_option == 4 || choose_option == 3)
			{
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					cnt_language = (cnt_language + 1) % 4;
				}

			}
			if (choose_option == 4 || choose_option == 3)
			{
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					cnt_language--;
					if (cnt_language < 0)
						cnt_language = 2;
				}
			}
			if ((choose_option == 6 || choose_option == 5) && (Keyboard::isKeyPressed(Keyboard::Enter)))
			{
				main_menu();
			}
		}
		if (cnt_language == 0 || cnt_language == 1)
			type_language = false;
		if (cnt_language == 2 || cnt_language == 3)
			type_language = true;
		//select option choice
		if (choose_option == 0 || choose_option == 7)
		{
			edit_sound.setFillColor(Color::Red);
			F_sound.setFillColor(Color::Red);
			edit_sound.setOutlineThickness(0);
			F_sound.setOutlineThickness(0);
		}
		else
		{
			edit_sound.setFillColor(Color::White);
			F_sound.setFillColor(Color::White);
			edit_sound.setOutlineThickness(1);
			F_sound.setOutlineThickness(1);
		}

		if (choose_option == 2 || choose_option == 1)
		{
			edit_music.setFillColor(Color::Red);
			edit_music.setOutlineThickness(0);
			F_music.setFillColor(Color::Red);
			F_music.setOutlineThickness(0);
		}
		else
		{
			edit_music.setFillColor(Color::White);
			edit_music.setOutlineThickness(1);
			F_music.setFillColor(Color::White);
			F_music.setOutlineThickness(1);
		}
		if (choose_option == 4 || choose_option == 3)
		{
			language.setFillColor(Color::Red);
			language.setOutlineThickness(0);
			F_language.setFillColor(Color::Red);
			F_language.setOutlineThickness(0);
		}
		else
		{
			language.setFillColor(Color::White);
			language.setOutlineThickness(1);
			F_language.setFillColor(Color::White);
			F_language.setOutlineThickness(1);
		}
		if (choose_option == 6 || choose_option == 5)
		{
			back.setFillColor(Color::Red);
			back.setOutlineThickness(0);
			F_back.setFillColor(Color::Red);
			F_back.setOutlineThickness(0);
		}
		else
		{
			back.setFillColor(Color::White);
			back.setOutlineThickness(1);
			F_back.setFillColor(Color::White);
			F_back.setOutlineThickness(1);
		}
		//show animation of turning the sound up and down
		if (cnt_volume_wasd != 0 && cnt_volume_wasd != 1)
		{
			volume_sound1.setFillColor(Color::Black);
		}
		else
			volume_sound1.setFillColor(Color::White);
		if (cnt_volume_wasd != 0 && cnt_volume_wasd != 2 && cnt_volume_wasd != 3 && cnt_volume_wasd != 1)
		{
			volume_sound2.setFillColor(Color::Black);
		}
		else
			volume_sound2.setFillColor(Color::White);
		if (cnt_volume_wasd != 0 && cnt_volume_wasd != 2 && cnt_volume_wasd != 4 && cnt_volume_wasd != 5 && cnt_volume_wasd != 1 && cnt_volume_wasd != 3)
		{
			volume_sound3.setFillColor(Color::Black);
		}
		else
			volume_sound3.setFillColor(Color::White);

		if (cnt_volume_wasd != 0 && cnt_volume_wasd != 2 && cnt_volume_wasd != 4 && cnt_volume_wasd != 6 && cnt_volume_wasd != 7 && cnt_volume_wasd != 1 && cnt_volume_wasd != 3 && cnt_volume_wasd != 5)
		{
			volume_sound4.setFillColor(Color::Black);

		}
		else
		{
			volume_sound4.setFillColor(Color::White);
		}
		if (cnt_volume_wasd != 0 && cnt_volume_wasd != 2 && cnt_volume_wasd != 4 && cnt_volume_wasd != 6 && cnt_volume_wasd != 8 && cnt_volume_wasd != 9 && cnt_volume_wasd != 1 && cnt_volume_wasd != 3 && cnt_volume_wasd != 5 && cnt_volume_wasd != 7)
		{

			volume_sound5.setFillColor(Color::Black);
		}
		else
			volume_sound5.setFillColor(Color::White);
		if (cnt_volume_wasd != 0 && cnt_volume_wasd != 2 && cnt_volume_wasd != 4 && cnt_volume_wasd != 6 && cnt_volume_wasd != 8 && cnt_volume_wasd != 10 && cnt_volume_wasd != 11 && cnt_volume_wasd != 1 && cnt_volume_wasd != 3 && cnt_volume_wasd != 5 && cnt_volume_wasd != 7 && cnt_volume_wasd != 9)
		{
			volume_sound6.setFillColor(Color::Black);
		}
		else
			volume_sound6.setFillColor(Color::White);
		//show animation of turning the music up and down
		if (cnt_music != 0 && cnt_music != 1)
		{

			volume_music1.setFillColor(Color::Black);
		}
		else
			volume_music1.setFillColor(Color::White);
		if (cnt_music != 0 && cnt_music != 2 && cnt_music != 3 && cnt_music != 1)
		{

			volume_music2.setFillColor(Color::Black);
		}
		else
			volume_music2.setFillColor(Color::White);
		if (cnt_music != 0 && cnt_music != 2 && cnt_music != 4 && cnt_music != 5 && cnt_music != 1 && cnt_music != 3)
		{

			volume_music3.setFillColor(Color::Black);
		}
		else
			volume_music3.setFillColor(Color::White);

		if (cnt_music != 0 && cnt_music != 2 && cnt_music != 4 && cnt_music != 6 && cnt_music != 7 && cnt_music != 1 && cnt_music != 3 && cnt_music != 5)
		{
			volume_music4.setFillColor(Color::Black);

		}
		else
			volume_music4.setFillColor(Color::White);

		if (cnt_music != 0 && cnt_music != 2 && cnt_music != 4 && cnt_music != 6 && cnt_music != 8 && cnt_music != 9 && cnt_music != 1 && cnt_music != 3 && cnt_music != 5 && cnt_music != 7)
		{

			volume_music5.setFillColor(Color::Black);
		}
		else
			volume_music5.setFillColor(Color::White);
		if (cnt_music != 0 && cnt_music != 2 && cnt_music != 4 && cnt_music != 6 && cnt_music != 8 && cnt_music != 10 && cnt_music != 11 && cnt_music != 1 && cnt_music != 3 && cnt_music != 5 && cnt_music != 7 && cnt_music != 9)
		{
			volume_music6.setFillColor(Color::Black);
		}
		else
			volume_music6.setFillColor(Color::White);
		if ((cnt_language == 0 || cnt_language == 1) && (choose_option == 4 || choose_option == 3))
		{
			choice_english.setFillColor(Color::Red);
		}
		else
		{
			choice_english.setFillColor(Color(0, 150, 600));
		}
		if ((cnt_language == 2 || cnt_language == 3) && (choose_option == 4 || choose_option == 3))
		{
			choice_francais.setFillColor(Color::Red);
		}
		else
		{
			choice_francais.setFillColor(Color(0, 150, 600));
		}
		if (cnt_language == 2 || cnt_language == 3)
		{
			type_language = true;
		}
		else
		{
			type_language = false;
		}
		music_Volume = 8.3f * cnt_music;
		sound_volume = 8.3f * cnt_volume_wasd;
		//draw
		window.clear();
		window.draw(Background);
		window.draw(Textbox);
		if (cnt_language == 0 || cnt_language == 1)
		{
			window.draw(option);
			window.draw(edit_sound);
			window.draw(edit_music);
			window.draw(language);
			window.draw(back);
		}
		if (cnt_language == 2 || cnt_language == 3)
		{
			window.draw(F_option);
			window.draw(F_sound);
			window.draw(F_music);
			window.draw(F_language);
			window.draw(F_back);
		}
		window.draw(volume_sound1);
		window.draw(volume_sound2);
		window.draw(volume_sound3);
		window.draw(volume_sound4);
		window.draw(volume_sound5);
		window.draw(volume_sound6);
		window.draw(volume_music1);
		window.draw(volume_music2);
		window.draw(volume_music3);
		window.draw(volume_music4);
		window.draw(volume_music5);
		window.draw(volume_music6);
		if (cnt_language == 0 || cnt_language == 1)
			window.draw(choice_english);
		if (cnt_language == 2 || cnt_language == 3)
			window.draw(choice_francais);
		if (cnt_volume_wasd > 6)
			window.draw(Volume_icon[0]);
		else if (cnt_volume_wasd > 1)
			window.draw(Volume_icon[1]);
		else if (cnt_volume_wasd == 1 || cnt_volume_wasd == 0)
			window.draw(Volume_icon[2]);
		if (cnt_music > 6)
			window.draw(Music_icon[0]);
		else if (cnt_music > 1)
			window.draw(Music_icon[1]);
		else
			window.draw(Music_icon[2]);
		if (choose_option == 4 || choose_option == 3)
		{
			window.draw(arrow1);
			window.draw(arrow2);
		}
		music.setVolume(music_Volume);
		switching.setVolume(sound_volume);
		window.display();
		//deltatime
		deltatime = gameclock.getElapsedTime().asSeconds();
	}
}
void choose_player_window(bool a, float music_Volume, int& x, int& x2)
{
	Texture background, left_icon, right_icon, faceset1[8], idleplayer1[8], faceset2[8], idleplayer2[8], choosedplayer1[8], choosedplayer2[8], right_icon2, left_icon2, shift;
	Sprite Background, Left_icon, Right_icon, Faceset1[8], Idleplayer1[8], Faceset2[8], Idleplayer2[8], Choosedplayer1[8], Choosedplayer2[8], Right_icon2, Left_icon2, Shift[4];
	Text title, order, player1, player2, ready, ready2, F_order, F_play, F_ready, F_Player1, F_player2, F_ready2, back_choose_player, play, F_back_choose_player, press[4], to[4],
		playername[2], namechanger[2], name[2], arrow[4];
	CircleShape arrow2(13.0, 3);
	int counter_pages = 1, cnt_player1 = 0, cnt_player2 = 0, k = 0, y2 = 0, i = 0, nselection = 1, y = 0;
	bool ischoosed = false, ischoosed2 = false, back_choose_select = false, language, name_selected = false, acccesss[3] = { 0,1 }, name_select = 0, name_typing = 0;
	float  delay = 0.3, timer = 0, delay2 = 0.3, timer2 = 0, deltatime2 = 0;
	Clock gameclock;
	Music ready_sound, not_ready_sound, switching, select_character, play_sound;
	language = a;
	//properties of background
	background.loadFromFile("./NinjaAdventure/Backgrounds/Tilesets/TilesetField.png");
	Background.setTextureRect(IntRect(0, 50, 60, 60));
	Background.setTexture(background);
	Background.setPosition(-500, -500);
	Background.setScale(100, 100);
	//music
	ready_sound.openFromFile("./NinjaAdventure/Sounds/Menu/Accept.wav");
	not_ready_sound.openFromFile("./NinjaAdventure/Sounds/Game/Alert.wav");
	switching.openFromFile("./NinjaAdventure/Sounds/Menu/Menu4.wav");
	select_character.openFromFile("./NinjaAdventure/Sounds/Game/MiniImpact.wav");
	play_sound.openFromFile("./NinjaAdventure/Sounds/Game/Success1.wav");
	//font
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	//text
	order.setFont(font);
	order.setString("CHOOSE     YOUR     CHARACTER");
	order.setPosition(430, 200);
	order.setFillColor(Color::Red);
	order.setCharacterSize(60);
	//-------------------------------
	player1.setFont(font);
	player1.setString("PLAYER   1");
	player1.setPosition(300, 300);
	player1.setFillColor(Color::Red);
	player1.setCharacterSize(50);
	//--------------------------------
	player2.setFont(font);
	player2.setString("PLAYER   2");
	player2.setPosition(1250, 300);
	player2.setFillColor(Color::Red);
	player2.setCharacterSize(50);
	//-------------------------------
	ready.setFont(font);
	ready.setString("READY");
	ready.setPosition(350, 750);
	ready.setFillColor(Color::Red);
	ready.setCharacterSize(50);
	//-------------------------------
	ready2.setFont(font);
	ready2.setString("READY");
	ready2.setPosition(1300, 750);
	ready2.setFillColor(Color::Red);
	ready2.setCharacterSize(50);
	//------------------------------
	play.setFont(font);
	play.setString("ENTER    FOR    PLAY");
	play.setPosition(590, 870);
	play.setFillColor(Color::Red);
	play.setCharacterSize(60);
	//-----------------------------
	back_choose_player.setFont(font);
	back_choose_player.setString("BACK");
	back_choose_player.setPosition(60, 30);
	back_choose_player.setFillColor(Color::White);
	back_choose_player.setCharacterSize(50);
	//-----------------------------
	press[0].setFont(font);
	press[0].setString("PRESS");
	press[0].setPosition(100, 750);
	press[0].setFillColor(Color::Red);
	press[0].setCharacterSize(45);
	//----------------------------
	to[0].setFont(font);
	to[0].setString("TO  GET  READY");
	to[0].setPosition(400, 750);
	to[0].setFillColor(Color::Red);
	to[0].setCharacterSize(45);
	//-----------------------------
	press[1].setFont(font);
	press[1].setString("PRESS");
	press[1].setPosition(1050, 750);
	press[1].setFillColor(Color::Red);
	press[1].setCharacterSize(45);
	//-----------------------------
	to[1].setFont(font);
	to[1].setString("TO  GET  READY");
	to[1].setPosition(1350, 750);
	to[1].setFillColor(Color::Red);
	to[1].setCharacterSize(45);
	//-----------------------------
	F_order.setFont(font);
	F_order.setString("CHOISIS     TON     HÉROS");
	F_order.setPosition(530, 200);
	F_order.setFillColor(Color::Red);
	F_order.setCharacterSize(60);
	//------------------------------
	F_Player1.setFont(font);
	F_Player1.setString("JOUEUR   1");
	F_Player1.setPosition(300, 300);
	F_Player1.setFillColor(Color::Red);
	F_Player1.setCharacterSize(50);
	//-------------------------------
	F_player2.setFont(font);
	F_player2.setString("JOUEUR   2");
	F_player2.setPosition(1250, 300);
	F_player2.setFillColor(Color::Red);
	F_player2.setCharacterSize(50);
	//-----------------------------
	F_ready.setFont(font);
	F_ready.setString("PRÊT");
	F_ready.setPosition(370, 750);
	F_ready.setFillColor(Color::Red);
	F_ready.setCharacterSize(50);
	//-----------------------------
	F_ready2.setFont(font);
	F_ready2.setString("PRÊT");
	F_ready2.setPosition(1320, 750);
	F_ready2.setFillColor(Color::Red);
	F_ready2.setCharacterSize(50);
	//-----------------------------
	F_play.setFont(font);
	F_play.setString("ENTRÉE  POUR  JOUER");
	F_play.setPosition(600, 850);
	F_play.setFillColor(Color::Red);
	F_play.setCharacterSize(60);
	//-----------------------------
	F_back_choose_player.setFont(font);
	F_back_choose_player.setString("DOS");
	F_back_choose_player.setPosition(60, 30);
	F_back_choose_player.setFillColor(Color::White);
	F_back_choose_player.setCharacterSize(50);
	//-----------------------------
	press[2].setFont(font);
	press[2].setString("APPUIES");
	press[2].setPosition(50, 750);
	press[2].setFillColor(Color::Red);
	press[2].setCharacterSize(40);
	//-----------------------------
	press[3].setFont(font);
	press[3].setString("APPUIES");
	press[3].setPosition(1050, 750);
	press[3].setFillColor(Color::Red);
	press[3].setCharacterSize(40);
	//-----------------------------
	to[2].setFont(font);
	to[2].setString("POUR  TU  PRÉPARER");
	to[2].setPosition(400, 750);
	to[2].setFillColor(Color::Red);
	to[2].setCharacterSize(40);
	//-----------------------------
	to[3].setFont(font);
	to[3].setString("POUR  TU  PRÉPARER");
	to[3].setPosition(1400, 750);
	to[3].setFillColor(Color::Red);
	to[3].setCharacterSize(40);
	//------------------------------
	name[0].setFont(font);
	name[0].setString("<-    NAME    ->");
	name[0].setPosition(788, 390);
	name[0].setFillColor(Color::Red);
	name[0].setCharacterSize(40);
	//------------------------------
	name[1].setFont(font);
	name[1].setString("<-    NOM    ->");
	name[1].setPosition(795, 390);
	name[1].setFillColor(Color::Red);
	name[1].setCharacterSize(40);
	//-------------------------------
	arrow[0].setFont(font);
	arrow[0].setString("<<");
	arrow[0].setPosition(650, 400);
	arrow[0].setFillColor(Color::Red);
	arrow[0].setCharacterSize(30);
	//-------------------------------
	arrow[1].setFont(font);
	arrow[1].setString(">>");
	arrow[1].setPosition(200, 400);
	arrow[1].setFillColor(Color::Red);
	arrow[1].setCharacterSize(30);
	//-------------------------------
	arrow[2].setFont(font);
	arrow[2].setString("<<");
	arrow[2].setPosition(1580, 400);
	arrow[2].setFillColor(Color::Red);
	arrow[2].setCharacterSize(30);
	//-------------------------------
	arrow[3].setFont(font);
	arrow[3].setString(">>");
	arrow[3].setPosition(1180, 400);
	arrow[3].setFillColor(Color::Red);
	arrow[3].setCharacterSize(30);
	//icons
	right_icon.loadFromFile("./NinjaAdventure/next.png");
	Right_icon.setTexture(right_icon);
	Right_icon.setPosition(580, 520);
	Right_icon.setScale(.08, .08);
	//-------------------------------
	left_icon.loadFromFile("./NinjaAdventure/back.png");
	Left_icon.setTexture(left_icon);
	Left_icon.setPosition(260, 512);
	Left_icon.setScale(.0907, .0907);
	//-------------------------------
	right_icon2.loadFromFile("./NinjaAdventure/next.png");
	Right_icon2.setTexture(right_icon2);
	Right_icon2.setPosition(1530, 520);
	Right_icon2.setScale(.08, .08);
	//-------------------------------
	left_icon2.loadFromFile("./NinjaAdventure/back.png");
	Left_icon2.setTexture(left_icon2);
	Left_icon2.setPosition(1210, 517);
	Left_icon2.setScale(.0907, .0907);
	//------------------------------
	shift.loadFromFile("./NinjaAdventure/icons/shift.png");
	Shift[0].setTexture(shift);
	Shift[0].setPosition(290, 730);
	Shift[0].setScale(.2, .2);
	//------------------------------
	shift.loadFromFile("./NinjaAdventure/icons/shift.png");
	Shift[1].setTexture(shift);
	Shift[1].setPosition(1235, 730);
	Shift[1].setScale(.2, .2);
	//------------------------------
	shift.loadFromFile("./NinjaAdventure/icons/shift.png");
	Shift[2].setTexture(shift);
	Shift[2].setPosition(290, 730);
	Shift[2].setScale(.2, .2);
	//------------------------------
	shift.loadFromFile("./NinjaAdventure/icons/shift.png");
	Shift[3].setTexture(shift);
	Shift[3].setPosition(1280, 730);
	Shift[3].setScale(.2, .2);
	//------------------------------
	arrow2.setPosition(20, 78);
	arrow2.setRotation(270);
	arrow2.setFillColor(Color::White);
	//properties array of faceset player1
	faceset1[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	faceset1[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	faceset1[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	faceset1[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	faceset1[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	faceset1[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	faceset1[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	faceset1[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	Faceset1[0].setTexture(faceset1[0]);
	Faceset1[0].setPosition(390, 490);
	Faceset1[0].setScale(2.5, 2.5);
	//-------------------------------

	Faceset1[1].setTexture(faceset1[1]);
	Faceset1[1].setPosition(390, 490);
	Faceset1[1].setScale(2.5, 2.5);
	//-------------------------------

	Faceset1[2].setTexture(faceset1[2]);
	Faceset1[2].setPosition(390, 490);
	Faceset1[2].setScale(2.5, 2.5);
	//-------------------------------

	Faceset1[3].setTexture(faceset1[3]);
	Faceset1[3].setPosition(390, 490);
	Faceset1[3].setScale(2.5, 2.5);
	//-------------------------------

	Faceset1[4].setTexture(faceset1[4]);
	Faceset1[4].setPosition(390, 490);
	Faceset1[4].setScale(2.5, 2.5);
	//-------------------------------

	Faceset1[5].setTexture(faceset1[5]);
	Faceset1[5].setPosition(390, 490);
	Faceset1[5].setScale(2.5, 2.5);
	//-------------------------------

	Faceset1[6].setTexture(faceset1[6]);
	Faceset1[6].setPosition(390, 490);
	Faceset1[6].setScale(2.5, 2.5);
	//-------------------------------

	Faceset1[7].setTexture(faceset1[7]);
	Faceset1[7].setPosition(390, 490);
	Faceset1[7].setScale(2.5, 2.5);
	//properties array of faceset player2
	faceset2[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	Faceset2[0].setTexture(faceset2[0]);
	Faceset2[0].setPosition(1340, 490);
	Faceset2[0].setScale(2.5, 2.5);
	//-------------------------------
	faceset2[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	Faceset2[1].setTexture(faceset2[1]);
	Faceset2[1].setPosition(1340, 490);
	Faceset2[1].setScale(2.5, 2.5);
	//-------------------------------
	faceset2[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	Faceset2[2].setTexture(faceset2[2]);
	Faceset2[2].setPosition(1340, 490);
	Faceset2[2].setScale(2.5, 2.5);
	//-------------------------------
	faceset2[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	Faceset2[3].setTexture(faceset2[3]);
	Faceset2[3].setPosition(1340, 490);
	Faceset2[3].setScale(2.5, 2.5);
	//file of sprites
	idleplayer1[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	idleplayer1[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	idleplayer1[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	idleplayer1[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	idleplayer1[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	idleplayer1[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	idleplayer1[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	idleplayer1[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	//-------------------------------
	idleplayer2[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	idleplayer2[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	idleplayer2[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	idleplayer2[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	//-------------------------------
	choosedplayer1[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Item.png");
	choosedplayer1[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Item.png");
	choosedplayer1[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Item.png");
	choosedplayer1[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Item.png");
	choosedplayer1[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Item.png");
	choosedplayer1[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Item.png");
	choosedplayer1[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Item.png");
	choosedplayer1[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Item.png");
	//-------------------------------
	choosedplayer2[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Item.png");
	choosedplayer2[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Item.png");
	choosedplayer2[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Item.png");
	choosedplayer2[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Item.png");
	//properties array of idle player1
	Idleplayer1[0].setTexture(idleplayer1[0]);
	Idleplayer1[0].setPosition(390, 620);
	Idleplayer1[0].setScale(6, 6);
	Idleplayer1[0].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer1[1].setTexture(idleplayer1[1]);
	Idleplayer1[1].setPosition(390, 620);
	Idleplayer1[1].setScale(6, 6);
	Idleplayer1[1].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer1[2].setTexture(idleplayer1[2]);
	Idleplayer1[2].setPosition(390, 620);
	Idleplayer1[2].setScale(6, 6);
	Idleplayer1[2].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer1[3].setTexture(idleplayer1[3]);
	Idleplayer1[3].setPosition(390, 620);
	Idleplayer1[3].setScale(6, 6);
	Idleplayer1[3].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer1[4].setTexture(idleplayer1[4]);
	Idleplayer1[4].setPosition(390, 620);
	Idleplayer1[4].setScale(6, 6);
	Idleplayer1[4].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer1[5].setTexture(idleplayer1[5]);
	Idleplayer1[5].setPosition(390, 620);
	Idleplayer1[5].setScale(6, 6);
	Idleplayer1[5].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer1[6].setTexture(idleplayer1[6]);
	Idleplayer1[6].setPosition(390, 620);
	Idleplayer1[6].setScale(6, 6);
	Idleplayer1[6].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer1[7].setTexture(idleplayer1[7]);
	Idleplayer1[7].setPosition(390, 620);
	Idleplayer1[7].setScale(6, 6);
	Idleplayer1[7].setTextureRect(IntRect(48, 0, 16, 16));
	//properties array of idle player2
	Idleplayer2[0].setTexture(idleplayer2[0]);
	Idleplayer2[0].setPosition(1340, 620);
	Idleplayer2[0].setScale(6, 6);
	Idleplayer2[0].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer2[1].setTexture(idleplayer2[1]);
	Idleplayer2[1].setPosition(1340, 620);
	Idleplayer2[1].setScale(6, 6);
	Idleplayer2[1].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer2[2].setTexture(idleplayer2[2]);
	Idleplayer2[2].setPosition(1340, 620);
	Idleplayer2[2].setScale(6, 6);
	Idleplayer2[2].setTextureRect(IntRect(48, 0, 16, 16));
	//-------------------------------
	Idleplayer2[3].setTexture(idleplayer2[3]);
	Idleplayer2[3].setPosition(1340, 620);
	Idleplayer2[3].setScale(6, 6);
	Idleplayer2[3].setTextureRect(IntRect(48, 0, 16, 16));
	//properties array of choosed player1
	Choosedplayer1[0].setTexture(choosedplayer1[0]);
	Choosedplayer1[0].setPosition(390, 620);
	Choosedplayer1[0].setScale(6, 6);
	//-------------------------------
	Choosedplayer1[1].setTexture(choosedplayer1[1]);
	Choosedplayer1[1].setPosition(390, 620);
	Choosedplayer1[1].setScale(6, 6);
	//-------------------------------
	Choosedplayer1[2].setTexture(choosedplayer1[2]);
	Choosedplayer1[2].setPosition(390, 620);
	Choosedplayer1[2].setScale(6, 6);
	//-------------------------------
	Choosedplayer1[3].setTexture(choosedplayer1[3]);
	Choosedplayer1[3].setPosition(390, 620);
	Choosedplayer1[3].setScale(6, 6);
	//-------------------------------
	Choosedplayer1[4].setTexture(choosedplayer1[4]);
	Choosedplayer1[4].setPosition(390, 620);
	Choosedplayer1[4].setScale(6, 6);
	//-------------------------------
	Choosedplayer1[5].setTexture(choosedplayer1[5]);
	Choosedplayer1[5].setPosition(390, 620);
	Choosedplayer1[5].setScale(6, 6);
	//-------------------------------
	Choosedplayer1[6].setTexture(choosedplayer1[6]);
	Choosedplayer1[6].setPosition(390, 620);
	Choosedplayer1[6].setScale(6, 6);
	//------------------------------
	Choosedplayer1[7].setTexture(choosedplayer1[7]);
	Choosedplayer1[7].setPosition(390, 620);
	Choosedplayer1[7].setScale(6, 6);
	//properties array of choosed player2
	Choosedplayer2[0].setTexture(choosedplayer2[0]);
	Choosedplayer2[0].setPosition(1340, 620);
	Choosedplayer2[0].setScale(6, 6);
	//-------------------------------
	Choosedplayer2[1].setTexture(choosedplayer2[1]);
	Choosedplayer2[1].setPosition(1340, 620);
	Choosedplayer2[1].setScale(6, 6);
	//-------------------------------
	Choosedplayer2[2].setTexture(choosedplayer2[2]);
	Choosedplayer2[2].setPosition(1340, 620);
	Choosedplayer2[2].setScale(6, 6);
	//-------------------------------
	Choosedplayer2[3].setTexture(choosedplayer2[3]);
	Choosedplayer2[3].setPosition(1340, 620);
	Choosedplayer2[3].setScale(6, 6);
	//name selector
	if (!name3.empty()) {
		name3.clear();
	}
	if (!name4.empty()) {
		name4.clear();
	}
	for (int i = 0; i < 2; i++)
	{
		namechanger[i].setFont(font);
		namechanger[i].setCharacterSize(36);
		namechanger[i].setFillColor(Color::Red);
		namechanger[i].setPosition(250 + i * 1000, 400);
	}
	//----------------------------------
	//while open
	while (window.isOpen())
	{
		namechanger[0].setPosition(425 - namechanger[0].getGlobalBounds().width / 2, 400);
		namechanger[1].setPosition(1395 - namechanger[1].getGlobalBounds().width / 2, 400);
		//walking animation of characters
		if (ischoosed == false)
		{
			if (timer < 0)
			{
				Idleplayer1[x].setTextureRect(IntRect(48, 16 * i, 16, 16));
				i++;
				i = i % 4;
				timer = delay;
			}
			else
				timer -= deltatime;
		}
		if (ischoosed2 == false)
		{
			if (timer2 < 0)
			{
				Idleplayer2[x2].setTextureRect(IntRect(48, 16 * k, 16, 16));
				k++;
				k = k % 4;
				timer2 = delay2;
			}
			else
				timer2 -= deltatime;
		}
		//show animation of choosing 
		if (ischoosed == true)
			Choosedplayer1[y].setTextureRect(IntRect(0, 0, 16, 16));
		if (ischoosed2 == true)
			Choosedplayer2[y2].setTextureRect(IntRect(0, 0, 16, 16));
		//----------------------------------
		gameclock.restart();
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{

				window.close();

			}
			//change characters of player 1
			if (Keyboard::isKeyPressed(Keyboard::D) && ischoosed == false && acccesss[2])
			{
				select_character.play();
				cnt_player1 = (cnt_player1 + 1) % 8;
				x = cnt_player1;
				y = cnt_player1;

			}
			if (Keyboard::isKeyPressed(Keyboard::A) && ischoosed == false && acccesss[2])
			{
				select_character.play();
				cnt_player1--;
				if (cnt_player1 < 0)
					cnt_player1 = 7;
				x = cnt_player1;
				y = cnt_player1;
			}
			//refering to BACK
			if (Keyboard::isKeyPressed(Keyboard::Up) && acccesss[1])
			{
				back_choose_select = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) && acccesss[0])
			{
				back_choose_select = false;
			}
			if (back_choose_select == true)
			{
				back_choose_player.setFillColor(Color::Red);
				F_back_choose_player.setFillColor(Color::Red);
				arrow2.setFillColor(Color::Red);
			}
			else if (back_choose_select == false)
			{
				back_choose_player.setFillColor(Color::White);
				F_back_choose_player.setFillColor(Color::White);
				arrow2.setFillColor(Color::White);
			}
			//switching between the functions
			if (back_choose_select == true && Keyboard::isKeyPressed(Keyboard::Enter) && acccesss[0])
			{
				main_menu();
			}
			if (ischoosed == true && ischoosed2 == true && Keyboard::isKeyPressed(Keyboard::Enter))
			{
				play_sound.play();
				level_select(language, music_Volume, name1, name2);
			}
			//player1 get ready
			if (Keyboard::isKeyPressed(Keyboard::LShift) && ischoosed == false && acccesss[2])
			{
				ischoosed = true;
				ready_sound.play();
			}
			else if (Keyboard::isKeyPressed(Keyboard::LShift) && ischoosed == true && acccesss[2])
			{
				ischoosed = false;
				not_ready_sound.play();
			}
			//change characters of player 2
			if (Keyboard::isKeyPressed(Keyboard::Right) && ischoosed2 == false && acccesss[2])
			{
				select_character.play();
				cnt_player2++;
				cnt_player2 = cnt_player2 % 4;
				x2 = cnt_player2;
				y2 = cnt_player2;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) && ischoosed2 == false && acccesss[2])
			{
				select_character.play();
				cnt_player2 = cnt_player2 - 1;
				if (cnt_player2 < 0)
					cnt_player2 = 3;
				x2 = cnt_player2;
				y2 = cnt_player2;
			}
			//player2 get ready
			if (Keyboard::isKeyPressed(Keyboard::RShift) && ischoosed2 == false && acccesss[2])
			{
				ischoosed2 = true;
				ready_sound.play();
			}
			else if (Keyboard::isKeyPressed(Keyboard::RShift) && ischoosed2 == true && acccesss[2])
			{
				ischoosed2 = false;
				not_ready_sound.play();
			}
			//name selector
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				nselection++;
				if (nselection > 3)
				{
					nselection = 3;
				}
				for (int i = 0; i < 3; i++)
				{
					acccesss[i] = 0;
				}
				switching.play();
				acccesss[nselection - 1] = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				nselection--;
				if (nselection < 1) {
					nselection = 1;
				}
				for (int i = 0; i < 3; i++) {
					acccesss[i] = 0;
				}
				switching.play();
				acccesss[nselection - 1] = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) && acccesss[1])
			{
				name_typing = 1;
				switching.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) && acccesss[1])
			{
				name_typing = 0;
				switching.play();
			}
			//static casting to char might not support various languages, remove it if needed but correct behavior isn't guaranteed then
			if (e.type == Event::TextEntered && !name_typing && acccesss[1]) {
				name3 += static_cast<char>(e.text.unicode);
			}
			if (e.type == Event::TextEntered && name_typing && acccesss[1]) {
				name4 += static_cast<char>(e.text.unicode);
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name3.size() > 0 && !name_typing && acccesss[1]) {
				name3.resize(name3.size() - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name4.size() > 0 && name_typing && acccesss[1]) {
				name4.resize(name4.size() - 1);
			}
			//name selector
			namechanger[0].setString(name3);
			namechanger[1].setString(name4);
		}
		//refering to write the name before choosing character
		if (!acccesss[2])
		{
			to[0].setFillColor(Color::White);
			to[1].setFillColor(Color::White);
			to[2].setFillColor(Color::White);
			to[3].setFillColor(Color::White);
			press[0].setFillColor(Color::White);
			press[1].setFillColor(Color::White);
			press[2].setFillColor(Color::White);
			press[3].setFillColor(Color::White);
			name[0].setFillColor(Color(178, 50, 50));
			name[1].setFillColor(Color(178, 50, 50));
			namechanger[0].setFillColor(Color(178, 50, 50));
			namechanger[1].setFillColor(Color(178, 50, 50));
		}
		else
		{
			to[0].setFillColor(Color::Red);
			to[1].setFillColor(Color::Red);
			to[2].setFillColor(Color::Red);
			to[3].setFillColor(Color::Red);
			press[0].setFillColor(Color::Red);
			press[1].setFillColor(Color::Red);
			press[2].setFillColor(Color::Red);
			press[3].setFillColor(Color::Red);
			name[0].setFillColor(Color::White);
			name[1].setFillColor(Color::White);
			namechanger[0].setFillColor(Color::White);
			namechanger[1].setFillColor(Color::White);
		}

		//draw
		window.clear();
		window.draw(Background);
		if (!type_language)
		{
			window.draw(order);
			window.draw(player1);
			window.draw(player2);
			//show ready text when players get ready
			if (ischoosed)
				window.draw(ready);
			else
			{
				window.draw(press[0]);
				window.draw(Shift[0]);
				window.draw(to[0]);
			}
			if (ischoosed2)
				window.draw(ready2);
			else
			{
				window.draw(press[1]);
				window.draw(Shift[1]);
				window.draw(to[1]);
			}
			window.draw(back_choose_player);
			if (ischoosed == true && ischoosed2 == true)
				window.draw(play);
			if (name_selected == false)
				window.draw(name[0]);
		}
		else
		{
			window.draw(F_order);
			window.draw(F_Player1);
			window.draw(F_player2);
			//show ready text when players get ready
			if (ischoosed)
				window.draw(F_ready);
			else
			{
				window.draw(press[2]);
				window.draw(Shift[2]);
				window.draw(to[2]);
			}
			if (ischoosed2)
				window.draw(F_ready2);
			else
			{
				window.draw(press[3]);
				window.draw(Shift[3]);
				window.draw(to[3]);
			}
			window.draw(F_back_choose_player);
			if (ischoosed == true && ischoosed2 == true)
				window.draw(F_play);
			if (name_selected == false)
				window.draw(name[1]);
		}
		window.draw(Right_icon);
		window.draw(Left_icon);
		window.draw(Right_icon2);
		window.draw(Left_icon2);
		window.draw(Faceset1[x]);
		window.draw(Faceset2[x2]);
		//animation of player1
		if (ischoosed == false)
		{

			window.draw(Idleplayer1[x]);
		}
		else
			window.draw(Choosedplayer1[y]);
		//animation of player2
		if (ischoosed2 == false)
		{

			window.draw(Idleplayer2[x2]);
		}
		else
			window.draw(Choosedplayer2[y2]);
		window.draw(arrow2);
		//name selector
		for (int i = 0; i < 2; i++)
		{
			window.draw(namechanger[i]);
		}
		if (!name_typing && acccesss[1])
		{
			window.draw(arrow[0]);
			window.draw(arrow[1]);
		}
		if (name_typing && acccesss[1])
		{
			window.draw(arrow[2]);
			window.draw(arrow[3]);
		}
		ready_sound.setVolume((sound_volume / 2.3));
		not_ready_sound.setVolume(sound_volume);
		switching.setVolume(sound_volume);
		select_character.setVolume(sound_volume);
		play_sound.setVolume(sound_volume);
		window.display();
		//deltatime
		deltatime = gameclock.getElapsedTime().asSeconds();
	}
}
void game_intro()
{
	Texture background, intro, engine_logo, idleplayer1[8];
	Sprite Background, Idleplayer1[8], Engine_logo, Intro;
	Font intro_font, engine_font;
	Text present[7], made, with;
	Clock gameclock;
	RectangleShape line(Vector2f(2, 90));
	float  delay = 0.3, timer = 0, sound = 100;
	int i = 0;
	background.loadFromFile("./NinjaAdventure/Backgrounds/Tilesets/TilesetField.png");
	Background.setTextureRect(IntRect(0, 50, 60, 60));
	Background.setTexture(background);
	Background.setPosition(-500, -500);
	Background.setScale(100, 100);
	intro.loadFromFile("./NinjaAdventure/icons/Screenshot_2024-03-29_133229-removebg-preview.png");
	Intro.setTexture(intro);
	Intro.setScale(1.5, 1.5);
	Intro.setPosition(450, 40);
	Intro.setColor(Color::White);
	idleplayer1[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	Idleplayer1[0].setTexture(idleplayer1[0]);
	Idleplayer1[0].setPosition(-200, 580);
	Idleplayer1[0].setScale(9, 9);
	Idleplayer1[0].setTextureRect(IntRect(48, 0, 16, 16));
	intro_font.loadFromFile("./NinjaAdventure/HUD/Font/KnightWarrior-w16n8.otf");
	engine_font.loadFromFile("./NinjaAdventure/HUD/Font/(A) Arslan Wessam A (A) Arslan Wessam A.ttf");
	present[0].setFont(intro_font);
	present[0].setString("P");
	present[0].setFillColor(Color::Black);
	present[0].setCharacterSize(80);
	present[0].setPosition(750, 600);
	present[1].setFont(intro_font);
	present[1].setString("R");
	present[1].setFillColor(Color::Black);
	present[1].setCharacterSize(80);
	present[1].setPosition(830, 600);
	present[2].setFont(intro_font);
	present[2].setString("E");
	present[2].setFillColor(Color::Black);
	present[2].setCharacterSize(80);
	present[2].setPosition(910, 600);
	present[3].setFont(intro_font);
	present[3].setString("S");
	present[3].setFillColor(Color::Black);
	present[3].setCharacterSize(80);
	present[3].setPosition(990, 600);
	present[4].setFont(intro_font);
	present[4].setString("E");
	present[4].setFillColor(Color::Black);
	present[4].setCharacterSize(80);
	present[4].setPosition(1070, 600);
	present[5].setFont(intro_font);
	present[5].setString("N");
	present[5].setFillColor(Color::Black);
	present[5].setCharacterSize(80);
	present[5].setPosition(1150, 600);
	present[6].setFont(intro_font);
	present[6].setString("T");
	present[6].setFillColor(Color::Black);
	present[6].setCharacterSize(80);
	present[6].setPosition(1230, 600);
	made.setFont(engine_font);
	made.setFillColor(Color::Black);
	made.setString("MADE");
	made.setCharacterSize(80);
	made.setPosition(800, 800);
	with.setFont(engine_font);
	with.setFillColor(Color::Black);
	with.setString("WITH");
	with.setCharacterSize(80);
	with.setPosition(800, 870);
	line.setPosition(980, 850);
	line.setFillColor(Color::Black);
	engine_logo.loadFromFile("./NinjaAdventure/icons/sfml-logo-small.png");
	Engine_logo.setTexture(engine_logo);
	Engine_logo.setScale(.8, .8);
	Engine_logo.setPosition(1000, 850);
	while (window.isOpen())
	{
		gameclock.restart();
		Idleplayer1[0].move(250 * deltatime, 0);
		if (timer < 0)
		{
			Idleplayer1[0].setTextureRect(IntRect(48, 16 * i, 16, 16));
			i++;
			i = i % 4;
			timer = delay;
		}
		else
			timer -= deltatime;
		while (window.pollEvent(e))
		{

			if (e.type == Event::Closed)
			{

				window.close();

			}
		}
		if (Idleplayer1[0].getPosition().x > 1900)
		{
			beginning_intro = false;
			main();
		}
		window.clear();
		window.draw(Background);
		window.draw(Intro);
		if (Idleplayer1[0].getPosition().x > 670)
			window.draw(present[0]);
		if (Idleplayer1[0].getPosition().x > 750)
			window.draw(present[1]);
		if (Idleplayer1[0].getPosition().x > 830)
			window.draw(present[2]);
		if (Idleplayer1[0].getPosition().x > 950)
			window.draw(present[3]);
		if (Idleplayer1[0].getPosition().x > 1050)
			window.draw(present[4]);
		if (Idleplayer1[0].getPosition().x > 1130)
			window.draw(present[5]);
		if (Idleplayer1[0].getPosition().x > 1180)
			window.draw(present[6]);
		window.draw(made);
		window.draw(with);
		window.draw(Idleplayer1[0]);
		window.draw(line);
		window.draw(Engine_logo);
		window.display();
		deltatime = gameclock.getElapsedTime().asSeconds();
	}
}
void level_select(bool a, float music_Volume, string& name1, string& name2)
{
	Texture background, textbox, banner, selected, lock;
	Sprite Background, Textbox, Banner, Box[3], Selected[3], Lock[2];
	Text level_select, level[3], back[2], F_back[2], F_level_select, enter_pass, F_enter_pass, playername[2], namechanger[2], enter_pass_button[2], F_enter_pass_button[2];
	CircleShape arrow(13.0, 3);
	bool up, back_button = false, language = a, enter_pass_bg1 = false, enter_pass_bg2 = false, acccesss[4] = { 1 }, pass1_selected = false,
		pass2_selected = false, pass_entered = false;
	int cnt_level = 7, nselection1 = 1, nselection2 = 1, back_pass = 0;
	string st_pass2 = "free", st_pass3 = "palestine", name0, name9;
	RectangleShape pass_bg(Vector2f(1920, 1080));
	Music switching, select_level_sound, enter_level;
	//properties of background
	background.loadFromFile("./NinjaAdventure/Backgrounds/Tilesets/TilesetField.png");
	Background.setTextureRect(IntRect(0, 50, 60, 60));
	Background.setTexture(background);
	Background.setPosition(-500, -500);
	Background.setScale(100, 100);
	//music
	switching.openFromFile("./NinjaAdventure/Sounds/Menu/Menu4.wav");
	select_level_sound.openFromFile("./NinjaAdventure/Sounds/Menu/Menu4.wav");
	//properties of textbox
	textbox.loadFromFile("./NinjaAdventure/HUD/Dialog/DialogueBoxSimple.png");
	Textbox.setTexture(textbox);
	Textbox.setPosition(490, 250);
	Textbox.setScale(3, 11);
	//propeties of banner
	banner.loadFromFile("./NinjaAdventure/icons/OIP__2_-removebg-preview.png");
	Banner.setTexture(banner);
	Banner.setPosition(1370, 320);
	Banner.setScale(.6, 3);
	Banner.setRotation(90);
	//properties of boxes
	Box[0].setTextureRect(IntRect(0, 145, 48, 45));
	Box[0].setTexture(background);
	Box[0].setPosition(600, 580);
	Box[0].setScale(3, 3);
	//--------------------------
	Box[1].setTextureRect(IntRect(0, 145, 48, 45));
	Box[1].setTexture(background);
	Box[1].setPosition(870, 580);
	Box[1].setScale(3, 3);
	//--------------------------
	Box[2].setTextureRect(IntRect(0, 145, 48, 45));
	Box[2].setTexture(background);
	Box[2].setPosition(1140, 580);
	Box[2].setScale(3, 3);
	//properties of selected
	selected.loadFromFile("./NinjaAdventure/HUD/Arrow.png");
	Selected[0].setTexture(selected);
	Selected[0].setPosition(650, 550);
	Selected[0].setScale(3, 3);
	//---------------------------
	Selected[1].setTexture(selected);
	Selected[1].setPosition(920, 550);
	Selected[1].setScale(3, 3);
	//---------------------------
	Selected[2].setTexture(selected);
	Selected[2].setPosition(1190, 550);
	Selected[2].setScale(3, 3);
	//properties of padlock
	lock.loadFromFile("./NinjaAdventure/icons/padlock.png");
	Lock[0].setTexture(lock);
	Lock[0].setPosition(905, 600);
	Lock[0].setScale(.15, .15);
	//----------------------------
	Lock[1].setTexture(lock);
	Lock[1].setPosition(1175, 600);
	Lock[1].setScale(.15, .15);
	//properties of pass_bg
	pass_bg.setPosition(0, 0);
	pass_bg.setFillColor(Color(0, 0, 0, 230));
	//text
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	level_select.setFont(font);
	level_select.setString("SELECT   LEVEL");
	level_select.setFillColor(Color::Red);
	level_select.setPosition(730, 360);
	level_select.setCharacterSize(50);
	//--------------------------
	level[0].setFont(font);
	level[0].setString("1");
	level[0].setFillColor(Color::Red);
	level[0].setPosition(655, 600);
	level[0].setCharacterSize(70);
	//--------------------------
	level[1].setFont(font);
	level[1].setString("2");
	level[1].setFillColor(Color::Red);
	level[1].setPosition(925, 600);
	level[1].setCharacterSize(70);
	//--------------------------
	level[2].setFont(font);
	level[2].setString("3");
	level[2].setFillColor(Color::Red);
	level[2].setPosition(1195, 600);
	level[2].setCharacterSize(70);
	//--------------------------
	back[0].setFont(font);
	back[0].setString("BACK");
	back[0].setPosition(60, 30);
	back[0].setFillColor(Color::White);
	back[0].setCharacterSize(50);
	//--------------------------
	enter_pass.setFont(font);
	enter_pass.setString("===   ENTER   PASSWORD   LEVEL   ===");
	enter_pass.setPosition(650, 300);
	enter_pass.setFillColor(Color::White);
	enter_pass.setCharacterSize(30);
	//--------------------------
	back[1].setFont(font);
	back[1].setString("=  BACK  =");
	back[1].setPosition(860, 650);
	back[1].setFillColor(Color::White);
	back[1].setCharacterSize(30);
	//--------------------------
	F_back[0].setFont(font);
	F_back[0].setString("DOS");
	F_back[0].setPosition(60, 30);
	F_back[0].setFillColor(Color::White);
	F_back[0].setCharacterSize(50);
	//---------------------------
	F_level_select.setFont(font);
	F_level_select.setString("CHOISIR  LE  NIVEAU");
	F_level_select.setFillColor(Color::Red);
	F_level_select.setPosition(650, 360);
	F_level_select.setCharacterSize(50);
	//----------------------------
	F_back[1].setFont(font);
	F_back[1].setString("=  DOS  =");
	F_back[1].setPosition(850, 650);
	F_back[1].setFillColor(Color::White);
	F_back[1].setCharacterSize(30);
	//----------------------------
	F_enter_pass.setFont(font);
	F_enter_pass.setString("===    ENTRER       LE       MOT       DE       PASSE       DU       NIVEAU    ===");
	F_enter_pass.setPosition(480, 300);
	F_enter_pass.setFillColor(Color::White);
	F_enter_pass.setCharacterSize(30);
	//-----------------------------
	F_enter_pass_button[0].setFont(font);
	F_enter_pass_button[0].setString("=  ENTERER  =");
	F_enter_pass_button[0].setPosition(810, 550);
	F_enter_pass_button[0].setFillColor(Color::White);
	F_enter_pass_button[0].setCharacterSize(30);
	//-----------------------------
	enter_pass_button[0].setFont(font);
	enter_pass_button[0].setString("=  ENTER  =");
	enter_pass_button[0].setPosition(850, 550);
	enter_pass_button[0].setFillColor(Color::White);
	enter_pass_button[0].setCharacterSize(30);
	//icons
	arrow.setPosition(20, 78);
	arrow.setRotation(270);
	arrow.setFillColor(Color::White);
	//name selector
	if (!name1.empty()) {
		name1.clear();
	}
	if (!name2.empty()) {
		name2.clear();
	}
	namechanger[0].setFont(font);
	namechanger[0].setCharacterSize(36);
	namechanger[0].setFillColor(Color::Red);
	namechanger[0].setPosition(880, 400);
	//------------------------------------
	namechanger[1].setFont(font);
	namechanger[1].setCharacterSize(36);
	namechanger[1].setFillColor(Color::Red);
	namechanger[1].setPosition(840, 400);
	//while_open
	while (window.isOpen())
	{
		gameclock.restart();
		while (window.pollEvent(e))
		{

			if (e.type == Event::Closed)
			{

				window.close();

			}
			//go to password window
			if ((cnt_level == 2 || cnt_level == 3) && Keyboard::isKeyPressed(Keyboard::Enter) && back_button == false && Pass2 == false)
				enter_pass_bg1 = true;
			if ((cnt_level == 4 || cnt_level == 5) && Keyboard::isKeyPressed(Keyboard::Enter) && back_button == false && Pass3 == false)
				enter_pass_bg2 = true;
			if ((cnt_level == 2 || cnt_level == 3) && Keyboard::isKeyPressed(Keyboard::Enter) && back_button == false && Pass2 == true)
			{
				music.stop();
				level2();
			}
			if ((cnt_level == 4 || cnt_level == 5) && Keyboard::isKeyPressed(Keyboard::Enter) && back_button == false && Pass3 == true)
			{
				music.stop();
				level3();
			}
			if ((cnt_level == 0 || cnt_level == 1) && Keyboard::isKeyPressed(Keyboard::Enter) && back_button == false)
			{
				music.stop();
				level1();
			}
			//get out of password window
			if (back_pass == 1 && Keyboard::isKeyPressed(Keyboard::Enter))
			{
				enter_pass_bg1 = false;
				enter_pass_bg2 = false;
				pass1_selected = false;
				pass2_selected = false;
				name1.clear();
				name2.clear();
			}

			//switch between the levels
			if (Keyboard::isKeyPressed(Keyboard::D) && back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			{
				select_level_sound.play();
				cnt_level = (cnt_level + 1) % 6;
				if (cnt_level > 3)
					cnt_level = 4;
			}
			if (Keyboard::isKeyPressed(Keyboard::A) && back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			{
				select_level_sound.play();
				cnt_level--;
				if (cnt_level < 0)
					cnt_level = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::W) && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			{
				switching.play();
				back_button = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S) && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			{
				switching.play();
				back_button = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up) && (enter_pass_bg1 == true || enter_pass_bg2 == true) && (Pass2 == false || Pass3 == false))
			{
				back_pass = (back_pass + 1) % 2;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) && (enter_pass_bg1 == true || enter_pass_bg2 == true) && (Pass2 == false || Pass3 == false))
			{
				back_pass--;
				if (back_pass < 0)
					back_pass = 1;
			}
			if (back_button == true && Keyboard::isKeyPressed(Keyboard::Enter) && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			{
				choose_player_window(language, music_Volume, x, y);
			}
			//name selector
			if (pass1_selected == false && enter_pass_bg1 == true)
			{
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					pass_entered = true;
					nselection1++;
					if (nselection1 > 1)
					{
						nselection1 = 1;
					}
					for (int i = 0; i < 1; i++)
					{
						acccesss[i] = 0;
					}
					acccesss[nselection1 - 1] = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					nselection1--;
					if (nselection1 < 1) {
						nselection1 = 1;
					}
					for (int i = 0; i < 1; i++) {
						acccesss[i] = 0;
					}
					acccesss[nselection1 - 1] = 1;
				}
			}
			if (pass2_selected == false && enter_pass_bg2 == true)
			{
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					nselection2++;
					if (nselection2 > 1)
					{
						pass2_selected = true;
					}
					for (int i = 0; i < 1; i++)
					{
						acccesss[i] = 0;
					}
					acccesss[nselection2 - 1] = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					nselection2--;
					if (nselection2 < 1) {
						nselection2 = 1;
					}
					for (int i = 0; i < 1; i++) {
						acccesss[i] = 0;
					}
					acccesss[nselection2 - 1] = 1;
				}
			}
			//static casting to char might not support various languages, remove it if needed but correct behavior isn't guaranteed then
			if (enter_pass_bg1 == true)
			{
				if (e.type == Event::TextEntered && acccesss[0]) {
					name1 += static_cast<char>(e.text.unicode);
				}
				if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name1.size() > 0 && acccesss[0]) {
					name1.resize(name1.size() - 1);
				}
			}
			if (enter_pass_bg2 == true)
			{
				if (e.type == Event::TextEntered && acccesss[0]) {
					name2 += static_cast<char>(e.text.unicode);
				}
				if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name2.size() > 0 && acccesss[0]) {
					name2.resize(name2.size() - 1);
				}
			}
			//name selector
			namechanger[0].setString(name1);
			namechanger[1].setString(name2);
		}
		if (enter_pass_bg1 && Keyboard::isKeyPressed(Keyboard::F8) && Keyboard::isKeyPressed(Keyboard::F10))
		{
			enter_pass_bg1 = false;
			Pass2 = true;
		}
		if (enter_pass_bg2 && Keyboard::isKeyPressed(Keyboard::F3) && Keyboard::isKeyPressed(Keyboard::F5))
		{
			Pass3 = true;
			enter_pass_bg2 = false;
		}
		//animation of selected arrow
		if (Selected[0].getPosition().y >= 540 && Selected[0].getPosition().y <= 550)
			up = false;
		if (Selected[0].getPosition().y <= 520 && Selected[0].getPosition().y >= 510)
			up = true;
		if (up == false && back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			Selected[0].move(0, -.2);
		else if (up == true && back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			Selected[0].move(0, .2);
		//-----------------------------
		if (Selected[1].getPosition().y >= 540 && Selected[1].getPosition().y <= 550)
			up = false;
		if (Selected[1].getPosition().y <= 520 && Selected[1].getPosition().y >= 510)
			up = true;
		if (up == false && back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			Selected[1].move(0, -.07);
		else if (up == true && back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			Selected[1].move(0, .07);
		//-----------------------------
		if (Selected[2].getPosition().y >= 540 && Selected[2].getPosition().y <= 550)
			up = false;
		if (Selected[2].getPosition().y <= 520 && Selected[2].getPosition().y >= 510)
			up = true;
		if (up == false && back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			Selected[2].move(0, -.07);
		else if (up == true && back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
			Selected[2].move(0, .07);
		//-----------------------------
		if (back_button == true && (enter_pass_bg1 == false && enter_pass_bg2 == false))
		{
			back[0].setFillColor(Color::Red);
			arrow.setFillColor(Color::Red);
			F_back[0].setFillColor(Color::Red);
		}
		else if (back_button == false && (enter_pass_bg1 == false && enter_pass_bg2 == false))
		{
			back[0].setFillColor(Color::White);
			arrow.setFillColor(Color::White);
			F_back[0].setFillColor(Color::White);
		}
		//-----------------------------
		if (back_pass == 1)
		{
			back[1].setFillColor(Color::Red);
			F_back[1].setFillColor(Color::Red);
			enter_pass_button[0].setFillColor(Color::White);
			F_enter_pass_button[0].setFillColor(Color::White);
		}
		else if (back_pass == 0)
		{
			back[1].setFillColor(Color::White);
			F_back[1].setFillColor(Color::White);
			enter_pass_button[0].setFillColor(Color::Red);
			F_enter_pass_button[0].setFillColor(Color::Red);
		}
		if (Pass2 == false)
			Box[1].setColor(Color(128, 128, 128));
		else
			Box[1].setColor(Color(255, 250, 250));
		if (Pass3 == false)
			Box[2].setColor(Color(128, 128, 128));
		else
			Box[2].setColor(Color(255, 250, 250));
		if (Pass3)
			Pass2 = true;
		//DRAW
		window.clear();
		window.draw(Background);
		window.draw(Textbox);
		window.draw(Banner);
		if (!type_language)
		{
			window.draw(level_select);
			window.draw(back[0]);
		}
		else
		{
			window.draw(F_level_select);
			window.draw(F_back[0]);
		}
		window.draw(Box[0]);
		window.draw(level[0]);
		window.draw(Box[1]);
		window.draw(Box[2]);
		if (Pass2 == true)
			window.draw(level[1]);
		else
			window.draw(Lock[0]);
		if (Pass3 == true)
			window.draw(level[2]);
		else
			window.draw(Lock[1]);
		window.draw(arrow);
		//draw the selected arrow
		if (cnt_level == 0 || cnt_level == 1)
			window.draw(Selected[0]);
		if (cnt_level == 2 || cnt_level == 3)
			window.draw(Selected[1]);
		if (cnt_level == 4 || cnt_level == 5)
			window.draw(Selected[2]);
		if ((enter_pass_bg1 == 1 || enter_pass_bg2 == true) && !type_language)
		{
			window.draw(pass_bg);
			window.draw(enter_pass);
			window.draw(back[1]);
			window.draw(enter_pass_button[0]);
		}
		else if ((enter_pass_bg1 == 1 || enter_pass_bg2 == true) && type_language)
		{
			window.draw(pass_bg);
			window.draw(F_enter_pass);
			window.draw(F_back[1]);
			window.draw(F_enter_pass_button[0]);
		}
		else
			back_pass = 0;
		//name selector
		if (enter_pass_bg1 == true)
			window.draw(namechanger[0]);
		if (enter_pass_bg2 == true)
			window.draw(namechanger[1]);
		switching.setVolume(sound_volume);
		select_level_sound.setVolume(sound_volume);
		window.display();
		//deltatime
		deltatime = gameclock.getElapsedTime().asSeconds();
	}
}
void main_menu()
{
	int choose_menu = 14;
	Texture background, textbox;
	Sprite Background, Textbox;
	Font font;
	menu Menu[2];
	Text  game_name;
	Music Music, switching;
	bool Language = false;
	//properties of background
	background.loadFromFile("./NinjaAdventure/Backgrounds/Tilesets/TilesetField.png");
	Background.setTextureRect(IntRect(0, 50, 60, 60));
	Background.setTexture(background);
	Background.setPosition(-600, -100);
	Background.setScale(100, 100);
	//music
	switching.openFromFile("./NinjaAdventure/Sounds/Menu/Menu4.wav");
	//properties of textbox
	textbox.loadFromFile("./NinjaAdventure/HUD/Dialog/DialogueBoxSimple.png");
	Textbox.setTexture(textbox);
	Textbox.setPosition(700, 250);
	Textbox.setScale(2, 12);
	//properties of texts
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	game_name.setFont(font);
	game_name.setString("PICO  PARK");
	game_name.setFillColor(Color::Red);
	game_name.setPosition(680, 100);
	game_name.setCharacterSize(110);
	//--------------------------
	Menu[0].edit_start.setFont(font);
	Menu[0].edit_start.setString("PLAY");
	Menu[0].edit_start.setFillColor(Color::White);
	Menu[0].edit_start.setOutlineThickness(1);
	Menu[0].edit_start.setOutlineColor(Color::Black);
	Menu[0].edit_start.setPosition(900, 370);
	Menu[0].edit_start.setCharacterSize(60);
	//--------------------------
	Menu[0].edit_option.setFont(font);
	Menu[0].edit_option.setString("OPTION");
	Menu[0].edit_option.setFillColor(Color::White);
	Menu[0].edit_option.setOutlineThickness(1);
	Menu[0].edit_option.setOutlineColor(Color::Black);
	Menu[0].edit_option.setPosition(860, 510);
	Menu[0].edit_option.setCharacterSize(60);
	//--------------------------
	Menu[0].credit.setFont(font);
	Menu[0].credit.setString("CREDIT");
	Menu[0].credit.setFillColor(Color::White);
	Menu[0].credit.setOutlineThickness(1);
	Menu[0].credit.setOutlineColor(Color::Black);
	Menu[0].credit.setPosition(860, 650);
	Menu[0].credit.setCharacterSize(60);
	//--------------------------
	Menu[0].edit_exit.setFont(font);
	Menu[0].edit_exit.setString("EXIT");
	Menu[0].edit_exit.setFillColor(Color::White);
	Menu[0].edit_exit.setOutlineThickness(1);
	Menu[0].edit_exit.setOutlineColor(Color::Black);
	Menu[0].edit_exit.setPosition(900, 780);
	Menu[0].edit_exit.setCharacterSize(60);
	//--------------------------
	Menu[1].edit_start.setFont(font);
	Menu[1].edit_start.setString("JOUER");
	Menu[1].edit_start.setFillColor(Color::White);
	Menu[1].edit_start.setOutlineThickness(1);
	Menu[1].edit_start.setOutlineColor(Color::Black);
	Menu[1].edit_start.setPosition(880, 370);
	Menu[1].edit_start.setCharacterSize(60);
	//--------------------------
	Menu[1].edit_option.setFont(font);
	Menu[1].edit_option.setString("PRAMÈTRES");
	Menu[1].edit_option.setFillColor(Color::White);
	Menu[1].edit_option.setOutlineThickness(1);
	Menu[1].edit_option.setOutlineColor(Color::Black);
	Menu[1].edit_option.setPosition(800, 510);
	Menu[1].edit_option.setCharacterSize(60);
	//--------------------------
	Menu[1].credit.setFont(font);
	Menu[1].credit.setString("CRÉDIT");
	Menu[1].credit.setFillColor(Color::White);
	Menu[1].credit.setOutlineThickness(1);
	Menu[1].credit.setOutlineColor(Color::Black);
	Menu[1].credit.setPosition(860, 650);
	Menu[1].credit.setCharacterSize(60);
	//--------------------------
	Menu[1].edit_exit.setFont(font);
	Menu[1].edit_exit.setString("SORTIE");
	Menu[1].edit_exit.setFillColor(Color::White);
	Menu[1].edit_exit.setOutlineThickness(1);
	Menu[1].edit_exit.setOutlineColor(Color::Black);
	Menu[1].edit_exit.setPosition(860, 780);
	Menu[1].edit_exit.setCharacterSize(60);
	while (window.isOpen()) {

		while (window.pollEvent(e))
		{

			if (e.type == Event::Closed)
			{

				window.close();

			}

			//switching between option choices
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				choose_menu = (choose_menu + 1) % 8;
				switching.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				choose_menu--;
				switching.play();
				if (choose_menu < 0)
					choose_menu = 7;
			}
			if (choose_menu == 0 || choose_menu == 1)
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					choose_player_window(Language, sound_volume, x, x2);
				}
			if (choose_menu == 2 || choose_menu == 3)
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					option_window(sound_volume, music_Volume);
				}
			if (choose_menu == 4 || choose_menu == 5)
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					music.stop();
					credit();
				}
			if ((choose_menu == 6 || choose_menu == 7) && (Keyboard::isKeyPressed(Keyboard::Enter)))
				window.close();
		}
		//selecting option choice
		if (choose_menu == 0 || choose_menu == 1)
		{
			Menu[0].edit_start.setFillColor(Color::Red);
			Menu[0].edit_start.setOutlineThickness(0);
			Menu[1].edit_start.setFillColor(Color::Red);
			Menu[1].edit_start.setOutlineThickness(0);
		}
		else
		{
			Menu[0].edit_start.setFillColor(Color::White);
			Menu[0].edit_start.setOutlineThickness(1);
			Menu[1].edit_start.setFillColor(Color::White);
			Menu[1].edit_start.setOutlineThickness(1);
		}
		if (choose_menu == 2 || choose_menu == 3)
		{
			Menu[0].edit_option.setFillColor(Color::Red);
			Menu[0].edit_option.setOutlineThickness(0);
			Menu[1].edit_option.setFillColor(Color::Red);
			Menu[1].edit_option.setOutlineThickness(0);
		}
		else
		{
			Menu[0].edit_option.setFillColor(Color::White);
			Menu[0].edit_option.setOutlineThickness(1);
			Menu[1].edit_option.setFillColor(Color::White);
			Menu[1].edit_option.setOutlineThickness(1);
		}
		if (choose_menu == 4 || choose_menu == 5)
		{
			Menu[0].credit.setFillColor(Color::Red);
			Menu[0].credit.setOutlineThickness(0);
			Menu[1].credit.setFillColor(Color::Red);
			Menu[1].credit.setOutlineThickness(0);
		}
		else
		{
			Menu[0].credit.setFillColor(Color::White);
			Menu[0].credit.setOutlineThickness(1);
			Menu[1].credit.setFillColor(Color::White);
			Menu[1].credit.setOutlineThickness(1);
		}
		if (choose_menu == 6 || choose_menu == 7)
		{
			Menu[0].edit_exit.setFillColor(Color::Red);
			Menu[0].edit_exit.setOutlineThickness(0);
			Menu[1].edit_exit.setFillColor(Color::Red);
			Menu[1].edit_exit.setOutlineThickness(0);
		}
		else
		{
			Menu[0].edit_exit.setFillColor(Color::White);
			Menu[0].edit_exit.setOutlineThickness(1);
			Menu[1].edit_exit.setFillColor(Color::White);
			Menu[1].edit_exit.setOutlineThickness(1);
		}
		//draw
		window.clear();
		window.draw(Background);
		window.draw(Textbox);
		window.draw(game_name);
		if (!type_language)
		{
			window.draw(Menu[0].edit_start);
			window.draw(Menu[0].edit_option);
			window.draw(Menu[0].credit);
			window.draw(Menu[0].edit_exit);
		}
		else
		{
			window.draw(Menu[1].edit_start);
			window.draw(Menu[1].edit_option);
			window.draw(Menu[1].credit);
			window.draw(Menu[1].edit_exit);
		}
		switching.setVolume(sound_volume);
		window.display();
	}
}
void level3()
{
	timer = 0;
	const float width = 1920;
	int ani = 0, a = 0, counter_fail_1 = 3, counter_fail_2 = 3, selector = 0, firex = 0, rightm1 = 0, veiwcom = 960, previousbutton3 = 0, previousbutton4 = 0;
	float speed = 4000, deltatime = 0, delay = 0.1f, timer = 0, gravity = 10.0f, timer2 = 0;
	bool up1 = false, up2 = false, up3 = false, back1 = false, checked = false, failed1 = false, failed2 = false, openess = 0, keyfree = 1, keyplayer = 0,
		endstage = 0, complete = 0, pause1 = 1, pause2 = 1, ending1 = false, ending2 = false, backm = false, letter_opened = false, previousbutton1 = 0,
		previousbutton2 = 0, collp1 = 0, collp2 = 0, to_next = false, is_int = false;
	Sprite player[8], player2[4], player_dead[8], player2_dead[4], hearts[3], hearts2[3], faceset[8], faceset2[4], Dooro, Doorc, Key, sign[3],
		Flag, Game_over, E_button, Letter, Shift, fire, cannon, Monster, Sand;
	Texture dooro, doorc, key, Sign, flag, heart, game_over, e_button, letter, shift, firetx, cannontx, monster, sand, back_ground, left_icon, right_icon, right_icon2,
		left_icon2, text_box, volume_icon[3] = {}, music_icon[3] = {};
	Music jump, fall, music, col_key;
	Text sign_text[6], check, retry, main_menu_text, F_retry, F_main, letter_text3[5], clear;
	RectangleShape pass_bg(Vector2f(1920, 1080));
	Clock animationclock100, animationclock200, gameclock2;
	//cannon
	Sign.loadFromFile("./NinjaAdventure/icons/sign.png");
	cannontx.loadFromFile("cannon.png");
	cannon.setTexture(cannontx);
	cannon.setPosition(5750, 850);
	firetx.loadFromFile("./NinjaAdventure/FX/Particle/Fire.png");
	fire.setTexture(firetx);
	fire.setScale(6, 3);
	fire.setTextureRect(IntRect(0, 0, 8, 12));
	animationclock100.restart();
	col_key.openFromFile("././NinjaAdventure/Sounds/Game/Coin.wav");
	music.openFromFile("./NinjaAdventure/Musics/29 - Lament.ogg");
	music.setLoop(true);
	music.play();
	sign[2].setTexture(Sign);
	sign[2].setScale(.2, .2);
	sign[2].setPosition(7100, 515);
	e_button.loadFromFile("./NinjaAdventure/icons/E.png");
	E_button.setTexture(e_button);
	E_button.setScale(1, 1);
	E_button.setPosition(7120, 450);
	letter.loadFromFile("./NinjaAdventure/icons/OIP__2_-removebg-preview.png");
	Letter.setTexture(letter);
	Letter.setScale(1.7, 1.15);
	Letter.setPosition(7100, 700);
	letter_text3[0].setFont(font);
	letter_text3[0].setCharacterSize(20);
	letter_text3[0].setPosition(7190, 750);
	letter_text3[0].setString("CONGRATULATIONS");
	letter_text3[0].setFillColor(Color::Black);
	letter_text3[1].setFont(font);
	letter_text3[1].setCharacterSize(20);
	letter_text3[1].setPosition(7235, 800);
	letter_text3[1].setString("GOOD   JOB");
	letter_text3[1].setFillColor(Color::Black);
	letter_text3[2].setFont(font);
	letter_text3[2].setCharacterSize(20);
	letter_text3[2].setPosition(7180, 850);
	letter_text3[2].setString("YOU   ARE   DONE   HERE");
	letter_text3[2].setFillColor(Color::Black);
	letter_text3[3].setFont(font);
	letter_text3[3].setCharacterSize(20);
	letter_text3[3].setPosition(7240, 900);
	letter_text3[3].setString("THANK   YOU");
	letter_text3[3].setFillColor(Color::Black);
	letter_text3[4].setFont(font);
	letter_text3[4].setCharacterSize(20);
	letter_text3[4].setPosition(7180, 950);
	letter_text3[4].setString("#FREE_PALESTINE");
	letter_text3[4].setFillColor(Color::Black);
	fall.openFromFile("./NinjaAdventure/Sounds/Game/Kill.wav");
	jump.openFromFile("./NinjaAdventure/Sounds/Game/Jump.wav");
	lvl3_intro(1920, 1080);
	window.setFramerateLimit(60);
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	dooro.loadFromFile("opened_door.png");
	doorc.loadFromFile("closed_door.png");
	key.loadFromFile("key.png");
	Key.setTexture(key);
	Dooro.setTexture(dooro);
	Doorc.setTexture(doorc);
	Key.setScale(.15f, .15f);
	Key.setPosition(2950, 640);
	Doorc.setScale(0.3f, 0.3f);
	Dooro.setScale(0.71f, 0.71f);
	Doorc.setPosition(7200, 355);
	Dooro.setPosition(7200, 355);
	sign[0].setTexture(Sign);
	sign[0].setScale(.2, .2);
	sign[0].setPosition(2600, 420);
	sign[1].setTexture(Sign);
	sign[1].setScale(.2, .2);
	sign[1].setPosition(5000, 770);
	//-----------------------------
	sign_text[0].setFont(font);
	sign_text[0].setCharacterSize(40);
	sign_text[0].setPosition(2640, 430);
	sign_text[0].setString("0");
	sign_text[0].setFillColor(Color::Red);
	sign_text[1].setFont(font);
	sign_text[1].setCharacterSize(40);
	sign_text[1].setPosition(2640, 430);
	sign_text[1].setString("1");
	sign_text[1].setFillColor(Color::Red);
	sign_text[2].setFont(font);
	sign_text[2].setCharacterSize(40);
	sign_text[2].setPosition(2640, 430);
	sign_text[2].setString("2");
	sign_text[2].setFillColor(Color::Red);
	sign_text[3].setFont(font);
	sign_text[3].setCharacterSize(40);
	sign_text[3].setPosition(5040, 780);
	sign_text[3].setString("0");
	sign_text[3].setFillColor(Color::Red);
	sign_text[4].setFont(font);
	sign_text[4].setCharacterSize(40);
	sign_text[4].setPosition(5040, 780);
	sign_text[4].setString("1");
	sign_text[4].setFillColor(Color::Red);
	sign_text[5].setFont(font);
	sign_text[5].setCharacterSize(40);
	sign_text[5].setPosition(5040, 780);
	sign_text[5].setString("2");
	sign_text[5].setFillColor(Color::Red);
	check.setFont(font);
	check.setCharacterSize(40);
	check.setPosition(3347, 347);
	check.setString("CHECK");
	check.setFillColor(Color::Red);
	flag.loadFromFile("./NinjaAdventure/Backgrounds/Animated/Flag/FlagYellow16x16.png");
	Flag.setTextureRect(IntRect(0, 0, 16, 16));
	Flag.setTexture(flag);
	Flag.setScale(6, 6);
	Flag.setPosition(3397, 417);
	//----------------------
	//heart
	heart.loadFromFile("./NinjaAdventure/icons/hearts.png");
	for (int i = 0; i < 3; i++)
	{
		hearts[i].setTexture(heart);
		hearts[i].setScale(.09f, .09f);
	}
	for (int i = 0; i < 3; i++)
	{
		hearts2[i].setTexture(heart);
		hearts2[i].setScale(.09f, .09f);
	}
	//game_over sprite
	game_over.loadFromFile("./NinjaAdventure/icons/game_over.png");
	Game_over.setTexture(game_over);
	name_player1.setFont(font);
	name_player1.setCharacterSize(20);
	name_player1.setString(name4);
	name_player1.setFillColor(Color(100, 50, 50));
	name_player2.setFont(font);
	name_player2.setCharacterSize(20);
	name_player2.setString(name3);
	name_player2.setFillColor(Color(100, 50, 50));
	//properties of pass_bg	
	pass_bg.setFillColor(Color(150, 0, 150));
	retry.setFont(font);
	retry.setString("RETRY");
	retry.setFillColor(Color::Red);
	retry.setCharacterSize(40);
	main_menu_text.setFont(font);
	main_menu_text.setString("MAIN    MENU");
	main_menu_text.setFillColor(Color::Red);
	main_menu_text.setCharacterSize(40);
	F_retry.setFont(font);
	F_retry.setString("RECOMMENCEZ");
	F_retry.setFillColor(Color::Red);
	F_retry.setCharacterSize(40);
	F_main.setFont(font);
	F_main.setString("MENU   PRINCIPAL");
	F_main.setFillColor(Color::Red);
	F_main.setCharacterSize(40);
	clear.setFont(font);
	clear.setCharacterSize(60);
	clear.setPosition(5740, 300);
	clear.setString("CLEAR");
	clear.setFillColor(Color::Red);
	shift.loadFromFile("./NinjaAdventure/icons/shift.png");
	Shift.setTexture(shift);
	Shift.setPosition(7340, 335);
	Shift.setScale(.15, .15);
	monster.loadFromFile("./NinjaAdventure/Actor/Monsters/Spirit/SpriteSheet.png");
	Monster.setTexture(monster);
	Monster.setTextureRect(IntRect(30, 0, 15, 15));
	Monster.setPosition(6000, 575);
	Monster.setScale(5, 5);
	Monster.setOrigin(8, 8);
	sand.loadFromFile("./NinjaAdventure/icons/TilesetElement.png");
	Sand.setTexture(sand);
	Sand.setPosition(5300, 580);
	Sand.setScale(7, 2);
	quads[0].position = Vector2f(0, 0);
	quads[1].position = Vector2f(1920, 0);
	quads[2].position = Vector2f(0, 1080);
	quads[3].position = Vector2f(1920, 1080);
	quads[0].color = Color(50, 10, 50, 255);
	quads[1].color = Color(100, 20, 100, 255);
	quads[2].color = Color(100, 40, 100, 255);
	quads[3].color = Color(200, 80, 200, 255);
	pinkback.setSize(Vector2f(1920, 1080));
	pinkback.setFillColor(Color(50, 10, 50, 255));
	//properties of texts
	to_lvlsell.setFont(font);
	to_lvlsell.setString("To level select");
	to_lvlsell.setFillColor(Color::Red);
	to_lvlsell.setPosition(width / 3 + 110, 100);
	to_lvlsell.setCharacterSize(45);
	//--------------------------
	to_main.setFont(font);
	to_main.setString("To MAIN MENU");
	to_main.setFillColor(Color::Red);
	to_main.setPosition(width / 3 + 110, 100);
	to_main.setCharacterSize(45);
	//--------------------------
	fto_lvlsell.setFont(font);
	fto_lvlsell.setString("sélection de niveau");
	fto_lvlsell.setFillColor(Color::Red);
	fto_lvlsell.setPosition(width / 3 + 110, 100);
	fto_lvlsell.setCharacterSize(36);
	//--------------------------
	fto_main.setFont(font);
	fto_main.setString("menu principal");
	fto_main.setFillColor(Color::Red);
	fto_main.setPosition(width / 3 + 110, 100);
	fto_main.setCharacterSize(36);
	//--------------------------
	option.setFont(font);
	option.setString("OPTIONS");
	option.setFillColor(Color::Red);
	option.setPosition(width / 3 + 110, 100);
	option.setCharacterSize(70);
	//--------------------------
	edit_sound.setFont(font);
	edit_sound.setString("SOUND");
	edit_sound.setFillColor(Color::White);
	edit_sound.setOutlineThickness(1);
	edit_sound.setOutlineColor(Color::Black);
	edit_sound.setPosition(width / 3 + 100, 240);
	edit_sound.setCharacterSize(40);
	//--------------------------
	edit_music.setFont(font);
	edit_music.setString("MUSIC");
	edit_music.setFillColor(Color::White);
	edit_music.setOutlineThickness(1);
	edit_music.setOutlineColor(Color::Black);
	edit_music.setPosition(width / 3 + 100, 380);
	edit_music.setCharacterSize(40);
	//--------------------------
	language.setFont(font);
	language.setString("LANGUAGE");
	language.setFillColor(Color::White);
	language.setOutlineThickness(1);
	language.setOutlineColor(Color::Black);
	language.setPosition(width / 3 + 100, 500);
	language.setCharacterSize(40);
	//---------------------------
	back.setFont(font);
	back.setString("BACK");
	back.setFillColor(Color::White);
	back.setOutlineThickness(1);
	back.setOutlineColor(Color::Black);
	back.setPosition(width / 3 + 100, 620);
	back.setCharacterSize(40);
	//---------------------------
	choice_english.setFont(font);
	choice_english.setString("ENGLISH");
	choice_english.setFillColor(Color::Transparent);
	choice_english.setPosition(width / 3 + 170, 560);
	choice_english.setCharacterSize(40);
	//---------------------------
	choice_francais.setFont(font);
	choice_francais.setString("FRANÇAIS");
	choice_francais.setFillColor(Color::Transparent);
	choice_francais.setPosition(width / 3 + 160, 562);
	choice_francais.setCharacterSize(38);
	//properties of texts in french
	F_option.setFont(font);
	F_option.setString("PRAMÈTRES");
	F_option.setFillColor(Color::Red);
	F_option.setPosition(width / 3 + 80, 110);
	F_option.setCharacterSize(60);
	//---------------------------
	F_sound.setFont(font);
	F_sound.setString("SON");
	F_sound.setFillColor(Color::White);
	F_sound.setOutlineThickness(1);
	F_sound.setOutlineColor(Color::Black);
	F_sound.setPosition(width / 3 + 100, 240);
	F_sound.setCharacterSize(40);
	//----------------------------
	F_music.setFont(font);
	F_music.setString("MUSIQUE");
	F_music.setFillColor(Color::White);
	F_music.setOutlineThickness(1);
	F_music.setOutlineColor(Color::Black);
	F_music.setPosition(width / 3 + 100, 380);
	F_music.setCharacterSize(40);
	//---------------------------
	F_language.setFont(font);
	F_language.setString("LANGUE");
	F_language.setFillColor(Color::White);
	F_language.setOutlineThickness(1);
	F_language.setOutlineColor(Color::Black);
	F_language.setPosition(width / 3 + 100, 500);
	F_language.setCharacterSize(40);
	//--------------------------
	F_back.setFont(font);
	F_back.setString("DOS");
	F_back.setFillColor(Color::White);
	F_back.setOutlineThickness(1);
	F_back.setOutlineColor(Color::Black);
	F_back.setPosition(width / 3 + 100, 620);
	F_back.setCharacterSize(40);
	//properties of textbox
	text_box.loadFromFile("./NinjaAdventure/HUD/Dialog/DialogueBoxSimple.png");
	Text_box.setTexture(text_box);
	Text_box.setPosition(width / 3 + 80, 190);
	Text_box.setScale(1.3, 9);
	//icons
	//sound icons
	volume_icon[0].loadFromFile("./NinjaAdventure/icons/volume-up-interface-symbol.png");
	Volume_icon[0].setTexture(volume_icon[0]);
	Volume_icon[0].setPosition(width / 3 + 100, 300);
	Volume_icon[0].setScale(.1, .1);
	volume_icon[1].loadFromFile("./NinjaAdventure/icons/volume.png");
	Volume_icon[1].setTexture(volume_icon[1]);
	Volume_icon[1].setPosition(width / 3 + 100, 305);
	Volume_icon[1].setScale(.08, .08);
	volume_icon[2].loadFromFile("./NinjaAdventure/icons/mute.png");
	Volume_icon[2].setTexture(volume_icon[2]);
	Volume_icon[2].setPosition(width / 3 + 93, 305);
	Volume_icon[2].setScale(.08, .08);
	//music icons
	music_icon[0].loadFromFile("./NinjaAdventure/icons/quaver.png");
	Music_icon[0].setTexture(music_icon[0]);
	Music_icon[0].setPosition(width / 3 + 100, 440);
	Music_icon[0].setScale(.1, .1);
	music_icon[1].loadFromFile("./NinjaAdventure/icons/music.png");
	Music_icon[1].setTexture(music_icon[1]);
	Music_icon[1].setPosition(width / 3 + 100, 440);
	Music_icon[1].setScale(.1, .1);
	music_icon[2].loadFromFile("./NinjaAdventure/icons/mute_music.png");
	Music_icon[2].setTexture(music_icon[2]);
	Music_icon[2].setPosition(width / 3 + 100, 445);
	Music_icon[2].setScale(.09, .09);
	//arrows of changing language
	arrow1.setPosition(width / 3 + 430, 577);
	arrow1.setRotation(90);
	arrow1.setFillColor(Color::Black);
	//--------------------------
	arrow2.setPosition(width / 3 + 126, 597);
	arrow2.setRotation(270);
	arrow2.setFillColor(Color::Black);
	scroll_down(choose_option);
	//Background
	Texture  backgroundTx;
	backgroundTx.loadFromFile("white.png");
	Sprite  background[2];
	for (int i = 0; i < 2; i++) {
		background[i].setTexture(backgroundTx);
		background[i].setPosition(Vector2f(i * 1920, 0));
		background[i].setScale(500, 500);
	}
	//View
	View view;
	View cameraView;
	cameraView.setSize(window.getSize().x, window.getSize().y - 100);
	//cameraView.setSize(1000 * 5, 1200 * 3);
	//Ground
	Texture Ground;
	Ground.loadFromFile("Ground.png");
	Sprite g[ng3];
	for (int i = 0; i < ng3; i++)
		g[i].setTexture(Ground);
	g[0].setPosition(0, 950);
	g[0].setScale(32, 10);
	g[1].setPosition(1800, 500);
	g[1].setScale(5, 5);
	g[2].setPosition(0, 0);
	g[2].setScale(1, 60);
	g[3].setPosition(2850, 500);
	g[3].setScale(5, 5);
	g[4].setPosition(3200, 500);
	g[4].setScale(1, 30);
	g[5].setPosition(3200, 500);
	g[5].setScale(3, 10);
	g[6].setPosition(3200, 620);
	g[6].setScale(4, 10);
	g[7].setPosition(3200, 740);
	g[7].setScale(5, 10);
	g[8].setPosition(3200, 860);
	g[8].setScale(6, 10);
	g[9].setPosition(5300, 600);
	g[9].setScale(5.6, 7.5);
	g[10].setPosition(5850, 600);
	g[10].setScale(1.4, 35);
	//g[11].setPosition(0, 0);
	//g[11].setScale(100, 5);
	//g[12].setPosition(5275, 600);//new
	//g[12].setScale(6.05, 0.5);
	g[13].setPosition(3150, 100);
	g[13].setScale(.2, 23.5);
	g[14].setPosition(1500, 800);
	g[14].setScale(2, 2);
	g[15].setPosition(4300, 950);
	g[15].setScale(0.6, 10);
	g[16].setPosition(4500, 950);
	g[16].setScale(0.6, 10);
	g[17].setPosition(4700, 950);
	g[17].setScale(0.6, 10);
	g[18].setPosition(6600, 600);
	g[18].setScale(0.8, 5);
	g[19].setPosition(6300, 600);
	g[19].setScale(0.8, 5);
	g[20].setPosition(6900, 600);
	g[20].setScale(4.7, 5);
	g[21].setPosition(7500, 0);
	g[21].setScale(1, 42.5);
	/*g[21].setPosition(6300, 190);
	g[21].setScale(0.7, 4);*/

	//Button

//Elevator

	Texture Elevator;
	Elevator.loadFromFile("Elevator.png");
	Sprite e[ne3];
	for (int i = 0; i < ne3; i++)
		e[i].setTexture(Elevator);
	e[0].setPosition(2450, 500);
	e[0].setScale(6, 4);
	e[1].setPosition(4850, 850);
	e[1].setScale(6, 4);
	//Spries
	PLAYERNEEDS_1 player_1;
	PLAYERNEEDS_2 player_2;
	player_1.walk[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	player_1.walk[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_1.walk[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_1.walk[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_1.walk[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_1.walk[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	player_1.walk[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	player_1.walk[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	//----------------------------------------------
	player_1.jump[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	player_1.jump[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_1.jump[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_1.jump[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_1.jump[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_1.jump[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	player_1.jump[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	player_1.jump[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	//-----------------------------------
	player_1.idle[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	player_1.idle[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_1.idle[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_1.idle[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_1.idle[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_1.idle[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	player_1.idle[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	player_1.idle[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	//-----------------------------------
	player_1.dead[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	player_1.dead[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_1.dead[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_1.dead[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_1.dead[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_1.dead[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	player_1.dead[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	player_1.dead[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	//------------------------------------
	player_1.faceset[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	player_1.faceset[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_1.faceset[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_1.faceset[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_1.faceset[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_1.faceset[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	player_1.faceset[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	player_1.faceset[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	player_1.scale = 5;
	player_1.jumpheight = 150.0f;
	//------------------------------------
	for (int i = 0; i < 8; i++)
	{
		player[i].setTexture(player_1.jump[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		player_dead[i].setTexture(player_1.dead[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		faceset[i].setTexture(player_1.faceset[i]);
	}
	faceset[x].setScale(2, 1);
	player_dead[x].setScale(6, 5);
	player[x].setScale(player_1.scale, player_1.scale);
	player[x].setPosition(300, 200);
	player[x].setOrigin(8, 8);
	//-------------------------------------
	player_2.walk[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	player_2.walk[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_2.walk[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_2.walk[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	//-------------------------------------
	player_2.jump[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	player_2.jump[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_2.jump[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_2.jump[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	//-------------------------------------
	player_2.idle[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	player_2.idle[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_2.idle[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_2.idle[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	//-------------------------------------
	player_2.dead[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	player_2.dead[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_2.dead[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_2.dead[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	//-------------------------------------
	player_2.faceset[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	player_2.faceset[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_2.faceset[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_2.faceset[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	player_2.scale = 5;
	player_2.jumpheight = 150.0f;
	//-------------------------------------
	for (int i = 0; i < 4; i++)
	{
		player2[i].setTexture(player_2.jump[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		player2_dead[i].setTexture(player_2.dead[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		faceset2[i].setTexture(player_2.faceset[i]);
	}
	faceset2[x2].setScale(2, 1);
	player2_dead[x2].setScale(6, 5);
	player2[x2].setScale(player_2.scale, player_2.scale);
	player2[x2].setPosition(200, 200);
	player2[x2].setOrigin(8, 8);
	Clock animationclock[6];
	for (int i = 0; i < 6; i++)
	{
		animationclock[i].restart();
	}
	int idlex1 = 0, idlex2 = 0;
	int righty1 = 0, righty2 = 0;
	int lefty1 = 0, lefty2 = 0;
	bool jumped = 0, jumped2 = 0, isAbove1 = 0, isAbove2 = 0;
	while (window.isOpen())
	{
		//Gameloop
		while (window.isOpen())
		{
			gameclock.restart();
			gameclock2.restart();
			Event event;
			name_player1.setPosition(player2[x2].getPosition().x - name_player2.getGlobalBounds().width / 2, player2[x2].getPosition().y - 100);
			name_player2.setPosition(player[x].getPosition().x - name_player1.getGlobalBounds().width / 2, player[x].getPosition().y - 100);
			pass_bg.setPosition(viewxcalc - window.getSize().x / 2.0, 0);
			retry.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0, pass_bg.getSize().y / 2.0 + 80);
			main_menu_text.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 50, pass_bg.getSize().y / 2.0 + 200);
			F_retry.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 100, pass_bg.getSize().y / 2.0 + 80);
			F_main.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 130, pass_bg.getSize().y / 2.0 + 200);
			Game_over.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 180, pass_bg.getSize().y / 2.0 - 250);
			player_dead[x].setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 + 20, pass_bg.getSize().y / 2.0 - 250);
			player2_dead[x2].setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 + 20, pass_bg.getSize().y / 2.0 - 250);
			pinkback.setPosition(viewxcalc - veiwcom, 0);
			quads[0].position = Vector2f(viewxcalc - veiwcom, 0);
			quads[1].position = Vector2f(viewxcalc + 1920 - veiwcom, 0);
			quads[2].position = Vector2f(viewxcalc - veiwcom, 1080);
			quads[3].position = Vector2f(viewxcalc + 1920 - veiwcom, 1080);
			option.setPosition(viewxcalc + 1920 / 3.f + 110 - veiwcom, 100);
			edit_sound.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 240);
			edit_music.setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 240);
			language.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 500);
			back.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 620);
			choice_english.setPosition(viewxcalc + 1920 / 3.f + 170 - veiwcom, 560);
			choice_francais.setPosition(viewxcalc + 1920 / 3.f + 160 - veiwcom, 562);
			F_option.setPosition(viewxcalc + 1920 / 3.f + 80 - veiwcom, 110);
			F_sound.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 240);
			F_music.setPosition(viewxcalc + 1920 / 3.f + 240 - veiwcom, 240);
			F_language.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 500);
			F_back.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 620);
			Text_box.setPosition(viewxcalc + 1920 / 3.f + 80 - veiwcom, 190);
			Volume_icon[0].setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 300);
			Volume_icon[1].setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 305);
			Volume_icon[2].setPosition(viewxcalc + 1920 / 3.f + 93 - veiwcom, 305);
			Music_icon[0].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
			Music_icon[1].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
			Music_icon[2].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
			arrow1.setPosition(viewxcalc + 1920 / 3.f + 430 - veiwcom, 577);
			arrow2.setPosition(viewxcalc + 1920 / 3.f + 126 - veiwcom, 597);
			to_lvlsell.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 360);
			to_main.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 430);
			fto_lvlsell.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 360);
			fto_main.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 430);
			for (int i = 0; i < 3; i++)
				hearts[i].setPosition(viewxcalc - 870 + 50 * i , window.getSize().y / 10.0);
			for (int i = 0; i < 3; i++)
				hearts2[i].setPosition(viewxcalc - 870 + 50 * i , window.getSize().y / 7.0);
			faceset[x].setPosition(viewxcalc - window.getSize().x / 2.0 , window.getSize().y / 10.0);
			faceset2[x2].setPosition(viewxcalc - window.getSize().x / 2.0, window.getSize().y / 7.0);
			if (animationclock100.getElapsedTime().asSeconds() >= 0.15) {

				fire.setTexture(firetx);

				fire.setTextureRect(IntRect(firex * 8, 0, 8, 12));
				firex++;
				firex %= 4;
				animationclock100.restart();
			}
			fire.move(-10, 0);
			for (int i = 0; i < ng3; i++) {
				if (fire.getGlobalBounds().intersects(g[i].getGlobalBounds()))
				{
					fire.setPosition(5750, 896);
				}
			}

			if (player[x].getGlobalBounds().intersects(fire.getGlobalBounds())) {
				counter_fail_1--;
				player[x].setPosition(3490, 200);
				player2[x2].setPosition(3590, 200);
				fall.play();
			}
			if (player2[x2].getGlobalBounds().intersects(fire.getGlobalBounds())) {
				counter_fail_2--;
				player[x].setPosition(3490, 200);
				player2[x2].setPosition(3590, 200);
				fall.play();
			}
			while (window.pollEvent(event)) {
				if ((Keyboard::isKeyPressed(Keyboard::Escape) && !previousbutton1) || (back_isselected() && Keyboard::isKeyPressed(Keyboard::Return) && !previousbutton2)) {
					if (!failed1 && !failed2 && !complete) {
						pause_unpause(gamecontrol);
						lang_update_anima();
					}
				}
				if (failed1 || failed2 || complete) {
					if (!gamecontrol)
						pause_unpause(gamecontrol);
				}
				previousbutton1 = Keyboard::isKeyPressed(Keyboard::Escape);
				previousbutton2 = Keyboard::isKeyPressed(Keyboard::Return);
				if (Keyboard::isKeyPressed(Keyboard::Right) && !gamecontrol) {
					if (!gamecontrol) {
						if (cnt_music != 4)
							turnup_music(choose_option, cnt_music);
						turnup_sound(choose_option, cnt_volume_wasd);
						lang_right(cnt_language);
						lang_update_anima();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Left) && !gamecontrol) {
					if (!gamecontrol) {
						turndown_sound(choose_option, cnt_volume_wasd);
						turndown_music(choose_option, cnt_music);
						lang_right(cnt_language);
						lang_update_anima();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::W) && !gamecontrol && !previousbutton3) {
					if (!gamecontrol) {
						scroll_up(choose_option);
						lang_update_anima();
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::S) && !gamecontrol && !previousbutton4) {
					scroll_down(choose_option);
					lang_update_anima();

				}
				if (Keyboard::isKeyPressed(Keyboard::Enter) && !gamecontrol && main_isselected()) {
					pause_unpause(gamecontrol);
					music.stop();
					cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
					cameraView.setSize(window.getSize().x, window.getSize().y);
					window.setView(cameraView);
					main_menu();
					beginning = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter) && !gamecontrol && select_isselected()) {
					pause_unpause(gamecontrol);
					music.stop();
					cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
					cameraView.setSize(window.getSize().x, window.getSize().y);
					window.setView(cameraView);
					level_select(type_language, music_Volume, name1, name2);
				}
				previousbutton3 = Keyboard::isKeyPressed(Keyboard::W);
				previousbutton4 = Keyboard::isKeyPressed(Keyboard::S);
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					selector = (selector + 1) % 4;
				}
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					selector--;
					if (selector < 0)
						selector = 3;
				}
				if ((selector == 0 || selector == 1) && Keyboard::isKeyPressed(Keyboard::Enter) && (failed1 || failed2))
				{
					music.stop();
					level3();
				}
				if ((selector == 2 || selector == 3) && Keyboard::isKeyPressed(Keyboard::Enter) && (failed1 || failed2))
				{
					music.stop();
					cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
					cameraView.setSize(window.getSize().x, window.getSize().y);
					window.setView(cameraView);
					beginning = true;
					main();
				}
				if (player[x].getGlobalBounds().intersects(sign[2].getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(sign[2].getGlobalBounds()))
					if (Keyboard::isKeyPressed(Keyboard::E))
						letter_opened = true;
					else if (player[x].getGlobalBounds().intersects(sign[2].getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(sign[2].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Escape))
						letter_opened = false;
				if (event.type == Event::Closed)
					window.close();
			}
			if (player2[x2].getGlobalBounds().intersects(Key.getGlobalBounds()) && keyfree) {
				col_key.play();
				keyfree = 0;
				keyplayer = 1;
			}
			if (player[x].getGlobalBounds().intersects(Key.getGlobalBounds()) && keyfree) {
				col_key.play();
				keyfree = 0;
				keyplayer = 0;
			}
			if (!keyplayer && !keyfree) {

				Key.setPosition(player[x].getPosition().x - 100, player[x].getPosition().y - 100);
			}
			if (keyplayer && !keyfree) {
				Key.setPosition(player2[x2].getPosition().x - 100, player2[x2].getPosition().y - 100);
			}
			if ((player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && !keyfree && !keyplayer) {

				Key.setScale(0, 0);
				endstage = 1;
			}
			if ((player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && !keyfree && keyplayer) {

				Key.setScale(0, 0);
				endstage = 1;
			}
			if (endstage) {
				openess = 1;
			}
			else {
				openess = 0;
			}
			if ((player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && openess) {
				pause1 = 0;
			}
			if ((player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && openess) {
				pause2 = 0;
			}
			if (player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds()) && openess && (player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds()))) {
				complete = 1;
			}
			if (selector == 0 || selector == 1)
			{
				retry.setFillColor(Color::Red);
				F_retry.setFillColor(Color::Red);
			}
			else
			{
				retry.setFillColor(Color::White);
				F_retry.setFillColor(Color::White);
			}
			if (selector == 2 || selector == 3)
			{
				main_menu_text.setFillColor(Color::Red);
				F_main.setFillColor(Color::Red);
			}
			else
			{
				main_menu_text.setFillColor(Color::White);
				F_main.setFillColor(Color::White);
			}

			//Animation
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i  mousepos = Mouse::getPosition(window);
				cout << mousepos.x << " " << mousepos.y << endl;
			}
			if (animationclock[0].getElapsedTime().asSeconds() >= 0.08) {
				for (int i = 0; i < 8; i++)
					player[i].setTexture(player_1.idle[i]);
				player[x].setTextureRect(IntRect(0, 0, 16, 16));
				/*player.setTextureRect(IntRect(idlex1 * 16, 0, 16, 16));
				idlex1++;
				idlex1 %= 4;*/
				animationclock[0].restart();
			}
			//e0 movement
			if (g[14].getPosition().y >= 920 && g[14].getPosition().y <= 930)
				up1 = false;
			if (g[14].getPosition().y <= 520 && g[14].getPosition().y >= 510)
				up1 = true;
			if (up1 == false && gamecontrol)
			{
				g[14].move(0, -1.5);
				if (player[x].getGlobalBounds().intersects(g[14].getGlobalBounds()) && player[x].getPosition().y < g[14].getPosition().y)
					player[x].move(0, -1.5);
				if (player2[x2].getGlobalBounds().intersects(g[14].getGlobalBounds()) && player2[x2].getPosition().y < g[14].getPosition().y)
					player2[x2].move(0, -1.5);
			}
			else if (up1 == true && gamecontrol)
			{
				g[14].move(0, 1.5);
				if (player[x].getGlobalBounds().intersects(g[14].getGlobalBounds()) && player[x].getPosition().y < g[14].getPosition().y)
					player[x].move(0, 1.5);
				if (player2[x2].getGlobalBounds().intersects(g[14].getGlobalBounds()) && player2[x2].getPosition().y < g[14].getPosition().y)
					player2[x2].move(0, 1.5);
			}
			//e1
			if ((!player[x].getGlobalBounds().intersects(e[0].getGlobalBounds()) || !player2[x2].getGlobalBounds().intersects(e[0].getGlobalBounds())) && e[0].getPosition().y >= 500 && gamecontrol)
			{
				e[0].move(0, -2);
				player[x].move(0, -2);
				player2[x2].move(0, -2);
				sign[0].move(0, -2);
				for (int i = 0; i < 3; i++)
					sign_text[i].move(0, -2);
			}
			else if (player[x].getGlobalBounds().intersects(e[0].getGlobalBounds()) && player2[x2].getGlobalBounds().intersects(e[0].getGlobalBounds()) && e[0].getPosition().y <= 900 && gamecontrol)
			{
				e[0].move(0, 2);
				if (player[x].getGlobalBounds().intersects(e[0].getGlobalBounds()))
					player[x].move(0, 2);
				if (player2[x2].getGlobalBounds().intersects(e[0].getGlobalBounds()))
					player2[x2].move(0, 2);
				sign[0].move(0, 2);
				for (int i = 0; i < 3; i++)
					sign_text[i].move(0, 2);
			}
			//e2 movement
			bool elevatorcol = 0, elevatorcol2 = 0, stop_move = 0;
			if (back1 == false)
			{
				g[13].move(-1.2, 0);
				elevatorcol = 1;
				if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && player[x].getPosition().x > g[13].getPosition().x)
					player[x].move(1.2, 0);
				if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Left) && player[x].getPosition().x > g[13].getPosition().x)
					player[x].move(10, 0);
				if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && player[x].getPosition().x < g[13].getPosition().x)
					player[x].move(-1.2, 0);
				if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Right) && player[x].getPosition().x < g[13].getPosition().x)
					player[x].move(-10, 0);
				if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && player2[x2].getPosition().x > g[13].getPosition().x)
					player2[x2].move(1.2, 0);
				if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::A) && player2[x2].getPosition().x > g[13].getPosition().x)
					player2[x2].move(10, 0);
				if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && player2[x2].getPosition().x < g[13].getPosition().x)
					player2[x2].move(-1.2, 0);
				if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::D) && player2[x2].getPosition().x < g[13].getPosition().x)
					player2[x2].move(-10, 0);
			}
			else if (back1 == true)
			{
				g[13].move(1.2, 0);
				if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && player[x].getPosition().x > g[13].getPosition().x)
					player[x].move(1.2, 0);
				if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Left) && player[x].getPosition().x > g[13].getPosition().x)
					player[x].move(10, 0);
				if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && player[x].getPosition().x < g[13].getPosition().x)
					player[x].move(-1.2, 0);
				if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Right) && player[x].getPosition().x < g[13].getPosition().x)
					player[x].move(-10, 0);
				if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && player2[x2].getPosition().x > g[13].getPosition().x)
					player2[x2].move(1.2, 0);
				if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::A) && player2[x2].getPosition().x > g[13].getPosition().x)
					player2[x2].move(10, 0);
				if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && player2[x2].getPosition().x < g[13].getPosition().x)
					player2[x2].move(-1.2, 0);
				if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::D) && player2[x2].getPosition().x < g[13].getPosition().x)
					player2[x2].move(-10, 0);
				elevatorcol2 = 1;
			}
			if (g[13].getPosition().x >= 2950 && g[13].getPosition().x <= 2960)
			{
				back1 = false;
			}
			if (g[13].getPosition().x <= 1880 && g[13].getPosition().x >= 1870)
				back1 = true;

			if (!backm)
			{
				Monster.move(-2, 0);
				Monster.setScale(5, 4);
				Monster.setTextureRect(IntRect(32, rightm1 * 16, 16, 16));
				if (animationclock200.getElapsedTime().asSeconds() >= 0.08) {
					rightm1++;
					rightm1 %= 4;
					animationclock200.restart();
				}
			}
			if (backm)
			{
				Monster.move(2, 0);
				Monster.setScale(-5, 4);
				Monster.setTextureRect(IntRect(32, rightm1 * 16, 16, 16));
				if (animationclock200.getElapsedTime().asSeconds() >= 0.08) {
					rightm1++;
					rightm1 %= 4;
					animationclock200.restart();
				}
			}
			if (Monster.getPosition().x <= 5600 && Monster.getPosition().x >= 5590)
				backm = true;
			if (Monster.getPosition().x >= 6000 && Monster.getPosition().x <= 6010)
				backm = false;
			//e3 movement 
			if (player[x].getGlobalBounds().intersects(e[1].getGlobalBounds()) && player2[x2].getGlobalBounds().intersects(e[1].getGlobalBounds()) && e[1].getPosition().y >= 600 && gamecontrol)
			{
				e[1].move(0, -2);
				player[x].move(0, -2);
				player2[x2].move(0, -2);
				sign[1].move(0, -2);
				for (int i = 3; i < 6; i++)
					sign_text[i].move(0, -2);
			}
			else if ((!player[x].getGlobalBounds().intersects(e[1].getGlobalBounds()) || !player2[x2].getGlobalBounds().intersects(e[1].getGlobalBounds())) && e[1].getPosition().y <= 850 && gamecontrol)
			{
				e[1].move(0, 2);
				if (player[x].getGlobalBounds().intersects(e[1].getGlobalBounds()))
					player[x].move(0, 2);
				if (player2[x2].getGlobalBounds().intersects(e[1].getGlobalBounds()))
					player2[x2].move(0, 2);
				sign[0].move(0, 2);
				for (int i = 0; i < 3; i++)
					sign_text[i].move(0, 2);
				sign[1].move(0, 2);
				for (int i = 3; i < 6; i++)
					sign_text[i].move(0, 2);
			}
			for (int i = 0; i < 2; i++)
			{
				if (i == 1)
					continue;
				if (player[x].getGlobalBounds().intersects(e[i].getGlobalBounds()) && !(Keyboard::isKeyPressed(Keyboard::Key::Up)))
					player[x].setPosition(player[x].getPosition().x, e[i].getPosition().y - 40);
				if (player2[x2].getGlobalBounds().intersects(e[i].getGlobalBounds()) && !(Keyboard::isKeyPressed(Keyboard::Key::W)))
					player2[x2].setPosition(player2[x2].getPosition().x, e[i].getPosition().y - 40);
			}
			if (animationclock[3].getElapsedTime().asSeconds() >= 0.08) {
				for (int i = 0; i < 4; i++)
				{
					player2[i].setTexture(player_2.idle[i]);
				}
				player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
				/*player2.setTextureRect(IntRect(idlex2 * 16, 0, 16, 16));
				idlex2++;
				idlex2 %= 4;*/
				animationclock[3].restart();
			}
			//Movement

			if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !ending1 && gamecontrol)
			{
				player[x].setScale(player_1.scale, player_1.scale);
				player[x].move(7, 0);
				for (int i = 0; i < 8; i++)
					player[i].setTexture(player_1.walk[i]);
				player[x].setTextureRect(IntRect(3 * 16, righty1 * 16, 16, 16));
				if (animationclock[1].getElapsedTime().asSeconds() >= 0.08) {
					righty1++;
					righty1 %= 4;
					animationclock[1].restart();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::D) && !ending2) {
				if (gamecontrol)
				{
					player2[x2].setScale(player_2.scale, player_2.scale);
					player2[x2].move(7, 0);
					for (int i = 0; i < 4; i++)
						player2[i].setTexture(player_2.walk[i]);
					player2[x2].setTextureRect(IntRect(3 * 16, righty2 * 16, 16, 16));
					if (animationclock[4].getElapsedTime().asSeconds() >= 0.08) {
						righty2++;
						righty2 %= 4;
						animationclock[4].restart();
					}
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !ending1 && gamecontrol)
			{
				player[x].setScale(player_1.scale, player_1.scale);
				player[x].move(-7, 0);
				for (int i = 0; i < 8; i++)
					player[i].setTexture(player_1.walk[i]);
				player[x].setTextureRect(IntRect(2 * 16, lefty1 * 16, 16, 16));
				if (animationclock[1].getElapsedTime().asSeconds() >= 0.08) {
					lefty1++;
					lefty1 %= 4;
					animationclock[1].restart();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::A) && !ending2)
			{
				if (gamecontrol)
				{
					player2[x2].setScale(player_2.scale, player_2.scale);
					player2[x2].move(-7, 0);
					for (int i = 0; i < 4; i++)
						player2[i].setTexture(player_2.walk[i]);
					player2[x2].setTextureRect(IntRect(2 * 16, lefty2 * 16, 16, 16));
					if (animationclock[4].getElapsedTime().asSeconds() >= 0.08) {
						lefty2++;
						lefty2 %= 4;
						animationclock[4].restart();
					}
				}
			}
			//collision with X
			for (int i = 0; i < ng3; i++)
			{
				if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Right) && g[i].getPosition().y < player[x].getPosition().y && !ending1)
				{
					if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
						player[x].move(-1, 0);
					player[x].move(-10, 0);
				}
				if (player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::D) && g[i].getPosition().y < player2[x2].getPosition().y && !ending2)
				{
					if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
						player[x].move(-1, 0);
					player2[x2].move(-10, 0);
				}
				if (player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::A) && g[i].getPosition().y < player2[x2].getPosition().y && !ending2)
				{
					if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
						player[x].move(-1, 0);
					player2[x2].move(10, 0);
				}
				if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Left) && g[i].getPosition().y < player[x].getPosition().y && !ending1)
				{
					if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
						player[x].move(-1, 0);
					player[x].move(10, 0);
				}
			}


			//JUMP AND GRAVITY

			//Player 1

			if ((!isGrounded_level3(player[x], g, e)) && !jumped && !isAbove1)
			{
				for (int i = 0; i < 8; i++)
					player[i].setTexture(player_1.jump[i]); //fall
				player[x].setTextureRect(IntRect(0, 0, 16, 16));
				//player.move(0, animationclk3.getElapsedTime().asSeconds()); WHEN UNCOMMENTED, PLAYER MOVES UP AND DOWN WHEN ON TOP OF THE OTHER PLAYER INSTEAD OF STAYING STILL
				player[x].move(0, 7);
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !jumped && !ending1 && gamecontrol)
				{
					if (!(failed1 || failed2))
						jump.play();
					jumped = 1;
					player_1.startposition = player[x].getPosition().y;
					animationclock[2].restart();
				}
			}

			if (jumped)
			{
				for (int i = 0; i < 8; i++)
					player[i].setTexture(player_1.jump[i]);
				if (Keyboard::isKeyPressed(Keyboard::Key::Left))
					player[x].setTextureRect(IntRect(2 * 16, 0, 16, 16));
				else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
					player[x].setTextureRect(IntRect(3 * 16, 0, 16, 16));
				else
					player[x].setTextureRect(IntRect(0 * 16, 0, 16, 16));
				player[x].move(0, -7);
				if (player_1.startposition - player[x].getPosition().y >= player_1.jumpheight) {
					jumped = 0;
					animationclock[2].restart();
				}
			}
			if (isGrounded_level3(player[x], g, e)) {
				for (int i = 0; i < 8; i++)
					player[i].setTexture(player_1.idle[i]);
				player[x].setTextureRect(IntRect(0, 0, 16, 16));
				if (Keyboard::isKeyPressed(Keyboard::Key::Right))
				{
					player[x].setScale(player_1.scale, player_1.scale);
					for (int i = 0; i < 8; i++)
						player[i].setTexture(player_1.walk[i]);
					player[x].setTextureRect(IntRect(3 * 16, righty1 * 16, 16, 16));
					if (animationclock[1].getElapsedTime().asSeconds() >= 0.08) {
						righty1++;
						righty1 %= 4;
						animationclock[1].restart();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Left))
				{
					player[x].setScale(player_1.scale, player_1.scale);
					for (int i = 0; i < 8; i++)
						player[i].setTexture(player_1.walk[i]);
					player[x].setTextureRect(IntRect(2 * 16, lefty1 * 16, 16, 16));
					if (animationclock[1].getElapsedTime().asSeconds() >= 0.08) {
						lefty1++;
						lefty1 %= 4;
						animationclock[1].restart();
					}
				}
			}
			//Player 2
			if ((!isGrounded_level3(player2[x2], g, e)) && !jumped2 && !isAbove2) //to fall down at first
			{
				for (int i = 0; i < 4; i++)
					player2[i].setTexture(player_2.jump[i]);
				player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
				//player2.move(0, animation2clk3.getElapsedTime().asSeconds() * 7); //WHEN UNCOMMENTED, PLAYER MOVES UP AND DOWN WHEN ON TOP OF THE OTHER PLAYER INSTEAD OF STAYING STILL
				player2[x2].move(0, 7);
			}
			else
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::W) && !jumped2 && !ending2 && gamecontrol)
				{
					if (!(failed1 || failed2))
						jump.play();
					jumped2 = 1;
					player_2.startposition = player2[x2].getPosition().y;
					animationclock[5].restart();
				}
			}
			if (jumped2)
			{
				for (int i = 0; i < 4; i++)
					player2[i].setTexture(player_2.jump[i]);
				if (Keyboard::isKeyPressed(Keyboard::Key::A))
					player2[x2].setTextureRect(IntRect(2 * 16, 0, 16, 16));
				else if (Keyboard::isKeyPressed(Keyboard::Key::D))
					player2[x2].setTextureRect(IntRect(3 * 16, 0, 16, 16));
				else
					player2[x2].setTextureRect(IntRect(0 * 16, 0, 16, 16));
				player2[x2].move(0, -7);
				if (player_2.startposition - player2[x2].getPosition().y >= player_2.jumpheight)
				{
					jumped2 = 0;
					animationclock[5].restart();
				}
			}
			if (isGrounded_level3(player2[x2], g, e)) {
				for (int i = 0; i < 4; i++)
					player2[i].setTexture(player_2.idle[i]);
				player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
				if (Keyboard::isKeyPressed(Keyboard::D)) {
					player2[x2].setScale(player_2.scale, player_2.scale);
					for (int i = 0; i < 4; i++)
						player2[i].setTexture(player_2.walk[i]);
					player2[x2].setTextureRect(IntRect(3 * 16, righty2 * 16, 16, 16));
					if (animationclock[4].getElapsedTime().asSeconds() >= 0.08) {
						righty2++;
						righty2 %= 4;
						animationclock[4].restart();
					}
				}

				if (Keyboard::isKeyPressed(Keyboard::Key::A))
				{
					player2[x2].setScale(player_2.scale, player_2.scale);
					for (int i = 0; i < 4; i++)
						player2[i].setTexture(player_2.walk[i]);
					player2[x2].setTextureRect(IntRect(2 * 16, lefty2 * 16, 16, 16));
					if (animationclock[4].getElapsedTime().asSeconds() >= 0.08) {
						lefty2++;
						lefty2 %= 4;
						animationclock[4].restart();
					}
				}

			}
			//PLAYER COLLISON 
			if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && ((player[x].getPosition().y > player2[x2].getPosition().y) || (player[x].getPosition().y < player2[x2].getPosition().y)))
			{
				if (player[x].getPosition().y < player2[x2].getPosition().y) {
					for (int i = 0; i < 8; i++)
						player[i].setTexture(player_1.idle[i]);
					player[x].setTextureRect(IntRect(0, 0, 16, 16));
					player[x].move(0, -7);
					isAbove1 = 1;
				}
				else if (player[x].getPosition().y > player2[x2].getPosition().y) {
					for (int i = 0; i < 4; i++)
						player2[i].setTexture(player_2.idle[i]);
					player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
					player2[x2].move(0, -7);
					isAbove2 = 1;
				}
			}
			else
			{
				isAbove1 = 0; isAbove2 = 0;
				if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Left))
					player[x].move(7, 0);
				if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Right))
					player[x].move(-7, 0);
				if (player2[x2].getGlobalBounds().intersects(player[x].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::A))
					player2[x2].move(7, 0);
				if (player2[x2].getGlobalBounds().intersects(player[x].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::D))
					player2[x2].move(-7, 0);
			}
			//COLLISION WITH MAP

			//	g[2]

			if (player2[x2].getGlobalBounds().intersects(g[2].getGlobalBounds()) && (Keyboard::isKeyPressed(Keyboard::Key::A) || jumped2))
			{
				player2[x2].move(7, 0);

				if (jumped2) {
					jumped2 = 0;
					player2[x2].move(0, 7);
				}
			}

			if (player[x].getGlobalBounds().intersects(g[2].getGlobalBounds()) && (Keyboard::isKeyPressed(Keyboard::Key::Left) || jumped))
			{
				player[x].move(7, 0);

				if (jumped) {
					jumped = 0;
					player[x].move(0, 7);
				}
			}
			//g[1]

			if (player[x].getGlobalBounds().intersects(g[1].getGlobalBounds()) && player[x].getPosition().y > g[1].getPosition().y) {

				player[x].move(0, 14);
				jumped = 0;

			}

			if (player2[x2].getGlobalBounds().intersects(g[1].getGlobalBounds()) && player2[x2].getPosition().y > g[1].getPosition().y) {

				player2[x2].move(0, 14);
				jumped2 = 0;

			}

			//g[3]

			if (player[x].getGlobalBounds().intersects(g[3].getGlobalBounds()) && player[x].getPosition().y > g[3].getPosition().y) {

				player[x].move(0, 14);
				jumped = 0;
			}
			if (player2[x2].getGlobalBounds().intersects(g[3].getGlobalBounds()) && player2[x2].getPosition().y > g[3].getPosition().y) {

				player2[x2].move(0, 14);
				jumped2 = 0;
			}
			//g[11]

			if (player[x].getGlobalBounds().intersects(g[11].getGlobalBounds())) {

				player[x].move(0, 14);


			}

			if (player2[x2].getGlobalBounds().intersects(g[11].getGlobalBounds())) {

				player2[x2].move(0, 14);


			}
			// e[0] 
			if (player[x].getGlobalBounds().intersects(g[14].getGlobalBounds()) && player[x].getPosition().y > g[14].getPosition().y) {

				player[x].move(0, 14);
				jumped = 0;

			}

			if (player2[x2].getGlobalBounds().intersects(g[14].getGlobalBounds()) && player2[x2].getPosition().y > g[14].getPosition().y) {

				player2[x2].move(0, 14);
				jumped2 = 0;

			}
			//e[1]
			if (player[x].getGlobalBounds().intersects(g[14].getGlobalBounds()) && player[x].getPosition().y > g[14].getPosition().y) {

				player[x].move(0, 14);
				jumped = 0;

			}
			if (player2[x2].getGlobalBounds().intersects(g[14].getGlobalBounds()) && player2[x].getPosition().y > g[14].getPosition().y) {

				player2[x2].move(0, 14);
				jumped2 = 0;
			}
			//e[2]
			if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && elevatorcol)
			{
				player2[x2].move(-8.2, 0);
				if (jumped2) {
					player2[x2].move(0, 7);
					jumped2 = 0;
				}
			}
			if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && elevatorcol2)

			{
				player2[x2].move(8.2, 0);

				if (jumped2) {
					jumped2 = 0;
					player2[x2].move(0, 7);
				}
			}

			if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && elevatorcol)
			{
				player[x].move(-8.2, 0);
				if (jumped) {
					jumped = 0;
					player[x].move(0, 7);
				}
			}
			if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && elevatorcol2)
			{
				player[x].move(8.2, 0);
				if (jumped) {
					jumped = 0;
					player[x].move(0, 7);
				}
			}
			if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && elevatorcol)
			{
				player2[x2].move(8.2, 0);
			}
			if (player2[x2].getGlobalBounds().intersects(g[13].getGlobalBounds()) && elevatorcol2)
			{
				player2[x2].move(-8.2, 0);
			}
			if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && elevatorcol)
			{
				player[x].move(8.2, 0);
			}
			if (player[x].getGlobalBounds().intersects(g[13].getGlobalBounds()) && elevatorcol2)
			{
				player[x].move(-8.2, 0);
			}
			if (player2[x2].getPosition().y >= g[14].getPosition().y && player2[x2].getPosition().x > 1500 && player2[x2].getPosition().x < 1700 && gamecontrol)
			{
				player2[x2].move(0, -.3);
				if (player2[x2].getGlobalBounds().intersects(g[14].getGlobalBounds()))
				{
					fall.play();
					player2[x2].setPosition(1400, 800);
					counter_fail_2--;
				}
			}
			if (player[x].getPosition().y >= g[14].getPosition().y && player[x].getPosition().x > 1500 && player2[x2].getPosition().x < 1700 && gamecontrol)
			{
				player[x].move(0, -.3);
				if (player[x].getGlobalBounds().intersects(g[14].getGlobalBounds()))
				{
					fall.play();
					player[x].setPosition(1400, 800);
					counter_fail_1--;
				}
			}
			if (player[x].getGlobalBounds().intersects(Flag.getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(Flag.getGlobalBounds()))
			{
				checked = true;
			}
			//View
			viewdeltax = abs(player[x].getPosition().x - player2[x2].getPosition().x);
			if (viewdeltax >= (window.getSize().x - player_1.idle[x].getSize().x)) {//player1 arrows ; player2 wasd
				extreme_x = 1; //can be used to pause calculation of viewxcalc for optimisation
			}
			else {
				extreme_x = 0;
			}
			if (extreme_x)
			{
				if (player[x].getPosition().x > player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::Right))
				{
					if (Keyboard::isKeyPressed(Keyboard::Key::A))
						player2[x2].move(7, 0);//or player2.move(-7,0);
					player[x].move(-7, 0);//or player1.move(7,0);
				}
				else if (player[x].getPosition().x > player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::A))
				{
					if (Keyboard::isKeyPressed(Keyboard::Key::Right))
						player[x].move(-7, 0);//or player2.move(-7,0);
					player2[x2].move(7, 0);//or player2.move(-7,0);
				}
				if (player[x].getPosition().x < player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::D))
				{
					if (Keyboard::isKeyPressed(Keyboard::Key::Left))
						player[x].move(7, 0);//or player1.move(-7,0);
					player2[x2].move(-7, 0);//or player2.move(7,0);
				}
				else if (player[x].getPosition().x < player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::Right))
				{
					if (Keyboard::isKeyPressed(Keyboard::Key::A))
						player2[x2].move(-7, 0);//or player1.move(-7,0);
					player[x].move(7, 0);//or player2.move(-7,0);
				}
			}
			if (timer < 3)
			{
				cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
				window.setView(cameraView);
			}
			else
			{
				viewxcalc = (player[x].getPosition().x + player2[x2].getPosition().x) / 2.f;//before window.clear
				if (viewxcalc < 1000)
					viewxcalc = 1000;
				cameraView.setCenter(viewxcalc, window.getSize().y - 450);
				if (viewxcalc > 6600)
					viewxcalc = 6600;
				cameraView.setCenter(viewxcalc, window.getSize().y - 450);
			}
			if (counter_fail_1 == 0)
			{
				failed1 = true;
			}
			if (counter_fail_2 == 0)
			{
				failed2 = true;
			}
			if (player[x].getPosition().y >= 900 && player[x].getPosition().y <= 910 && player[x].getPosition().x > 5500) {
				fall.play();
			}
			if (player2[x2].getPosition().y >= 900 && player2[x2].getPosition().y <= 910 && player2[x2].getPosition().x > 5500) {
				fall.play();
			}
			if (player[x].getPosition().y >= 1000 && player[x].getPosition().y <= 1010 && player[x].getPosition().x < 5500) {
				fall.play();
			}
			if (player2[x2].getPosition().y >= 1000 && player2[x2].getPosition().y <= 1010 && player2[x2].getPosition().x < 5500)
			{
				fall.play();
			}
			if (player[x].getPosition().y >= 1080)
			{
				player[x].setPosition(3500, 200);
				player2[x2].setPosition(3600, 200);
				ending1 = false;
				ending2 = false;
				counter_fail_1--;
			}
			if (player2[x2].getPosition().y >= 1080)
			{
				player[x].setPosition(3500, 200);
				player2[x2].setPosition(3600, 200);
				ending1 = false;
				ending2 = false;
				counter_fail_2--;
			}
			if (player[x].getGlobalBounds().intersects(Monster.getGlobalBounds()))
			{
				fall.play();
				player[x].setPosition(3500, 200);
				player2[x2].setPosition(3600, 200);
				ending1 = false;
				ending2 = false;
				counter_fail_1--;
			}
			if (player2[x2].getGlobalBounds().intersects(Monster.getGlobalBounds()))
			{
				fall.play();
				player[x].setPosition(3500, 200);
				player2[x2].setPosition(3600, 200);
				ending1 = false;
				ending2 = false;
				counter_fail_2--;
			}
			if (timer2 > 5)
			{
				music.stop();
				cameraView.setCenter(1920 / 2, 1080 / 2);
				cameraView.setSize(1920, 1080);
				window.setView(cameraView);
				credit();
			}
			if (!ending1 && player[x].getGlobalBounds().intersects(Dooro.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::RShift) && openess)
				ending1 = true;
			else if (ending1 && Keyboard::isKeyPressed(Keyboard::Key::RShift) && !ending2)
				ending1 = false;
			if (!ending2 && player2[x2].getGlobalBounds().intersects(Dooro.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::LShift) && openess)
				ending2 = true;
			else if (ending2 && Keyboard::isKeyPressed(Keyboard::Key::LShift) && !ending1)
				ending2 = false;
			window.setView(cameraView);
			window.clear();
			for (int i = 0; i < 2; i++)
				window.draw(background[i]);
			//Draw Map
			window.draw(Flag);
			window.draw(Sand);
			window.draw(sign[2]);
			for (int i = 0; i < ng3; i++)
				window.draw(g[i]);
			window.draw(Key);
			if (openess) {
				window.draw(Dooro);
			}
			else
				window.draw(Doorc);
			if (!is_int)
			{
				for (int i = 0; i < counter_fail_1; i++)
					window.draw(hearts[i]);
				for (int i = 0; i < counter_fail_2; i++)
					window.draw(hearts2[i]);
				window.draw(faceset[x]);
				window.draw(faceset2[x2]);
			}
			if (!ending2)
				window.draw(name_player1);
			if (!ending1)
				window.draw(name_player2);
			window.draw(sign[0]);
			window.draw(sign[1]);
			for (int i = 0; i < ne3; i++)
				window.draw(e[i]);
			if (player[x].getGlobalBounds().intersects(e[0].getGlobalBounds()) && player2[x2].getGlobalBounds().intersects(e[0].getGlobalBounds()))
				window.draw(sign_text[0]);
			else if (!(player[x].getGlobalBounds().intersects(e[0].getGlobalBounds())) && !(player2[x2].getGlobalBounds().intersects(e[0].getGlobalBounds())))
			{

				window.draw(sign_text[2]);
			}
			else
				window.draw(sign_text[1]);
			if (player[x].getGlobalBounds().intersects(e[1].getGlobalBounds()) && player2[x2].getGlobalBounds().intersects(e[1].getGlobalBounds()))
				window.draw(sign_text[3]);
			else if (!(player[x].getGlobalBounds().intersects(e[1].getGlobalBounds())) && !(player2[x2].getGlobalBounds().intersects(e[1].getGlobalBounds())))
			{

				window.draw(sign_text[5]);
			}
			else
				window.draw(sign_text[4]);
			if (checked)
				window.draw(check);
			if (player[x].getGlobalBounds().intersects(sign[2].getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(sign[2].getGlobalBounds()))
				window.draw(E_button);
			if (!ending1)
			{
				window.draw(player[x]);
				player[x].setScale(5, 5);
			}
			else
				player[x].setScale(.1, .1);
			if (!ending2)
			{
				window.draw(player2[x2]);
				player2[x2].setScale(5, 5);
			}
			else
				player2[x2].setScale(.1, .1);
			if (timer < 3)
			{
				embeddeddraw_intro_lvl3();
				is_int = true;
			}
			else
				is_int = 0;
			window.draw(cannon);
			window.draw(fire);
			if (letter_opened)
			{
				window.draw(Letter);
				for (int i = 0; i < 5; i++)
					window.draw(letter_text3[i]);
			}
			window.draw(Monster);
			if (ending1 && ending2)
			{
				music.stop();
				window.draw(clear);
				if (clear.getPosition().x <= 6500)
					clear.move(20, 0);
				else
					to_next = true;
			}
			else
				if ((player[x].getGlobalBounds().intersects(Dooro.getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(Dooro.getGlobalBounds())) && !ending1 && !ending2)
					window.draw(Shift);
			if (cnt_music == 0)
				music.stop();
			else if (cnt_music == 1)
			{
				music.play();
				cnt_music = 4;
				music.setVolume(music_Volume * cnt_music);
			}
			jump.setVolume(sound_volume * cnt_volume_wasd);
			fall.setVolume(sound_volume * cnt_volume_wasd);
			col_key.setVolume(sound_volume * cnt_volume_wasd);
			embedded_draw_pause();
			if (failed1 || failed2)
			{
				music.stop();
				window.draw(pass_bg);
				if (!type_language)
				{
					window.draw(retry);
					window.draw(main_menu_text);
				}
				else
				{
					window.draw(F_retry);
					window.draw(F_main);
				}
				window.draw(Game_over);
				if (counter_fail_1 == 0)
					window.draw(player_dead[x]);
				if (counter_fail_2 == 0)
					window.draw(player2_dead[x2]);
			}
			window.display();
			deltatime = gameclock.getElapsedTime().asSeconds();
			timer += gameclock.getElapsedTime().asSeconds();
			if (to_next)
				timer2 += gameclock2.getElapsedTime().asSeconds();
		}
	}
}
void level1()
{
	timer = 0;
	window.setFramerateLimit(60);
	const float width = 1920;
	bool failed1 = false, failed2 = false, button_pressed = false, checked = false, fallen[29] = {}, openess = 0, keyfree = 1,
		keyplayer = 0, endstage = 0, complete = 0, pause1 = 1, pause2 = 1, letter_opened = false, ending1 = false, ending2 = false,
		to_next = false, previousbutton1 = 0, previousbutton2 = 0, collp1 = 0, collp2 = 0, is_int = 0,button_sound=0;
	Texture game_over, heart, Sign, flag, dooro, doorc, key, e_button, letter, shift, back_ground, left_icon, right_icon, right_icon2
		, left_icon2, text_box, volume_icon[3] = {}, music_icon[3] = {};
	int selector = 0, i = 0, veiwcom = 960, previousbutton3 = 0, previousbutton4 = 0, counter_fail_1 = 3, counter_fail_2 = 3;;
	Sprite player[8], player2[4], Game_over, player_dead[8], player2_dead[4], hearts[3], hearts2[3], faceset[8], faceset2[4], sign[2],
		Flag, Dooro, Doorc, Key, E_button, Letter, Shift;
	RectangleShape pass_bg(Vector2f(1920, 1080));
	Text retry, main_menu_text, lose_text, sign_text[3], F_retry, F_main, check, letter_text[5], clear;
	Music jump, fall, music, col_key;
	float timer2 = 0;
	Clock gameclock2;
	col_key.openFromFile("././NinjaAdventure/Sounds/Game/Coin.wav");
	music.openFromFile("./NinjaAdventure/Musics/23 - Road.ogg");
	music.setLoop(true);
	music.play();
	check.setFont(font);
	check.setCharacterSize(40);
	check.setPosition(6050, 350);
	check.setString("CHECK");
	check.setFillColor(Color::Red);
	flag.loadFromFile("./NinjaAdventure/Backgrounds/Animated/Flag/FlagYellow16x16.png");
	Flag.setTextureRect(IntRect(0, 0, 16, 16));
	Flag.setTexture(flag);
	Flag.setScale(6, 6);
	Flag.setPosition(6100, 420);
	fall.openFromFile("./NinjaAdventure/Sounds/Game/Kill.wav");
	jump.openFromFile("./NinjaAdventure/Sounds/Game/Jump.wav");
	lvl1_intro(1920, 1080);
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	Sign.loadFromFile("./NinjaAdventure/icons/sign.png");
	sign[0].setTexture(Sign);
	sign[0].setScale(.2, .2);
	sign[0].setPosition(5650, 815);
	sign[1].setTexture(Sign);
	sign[1].setScale(.2, .2);
	sign[1].setPosition(8550, 420);
	e_button.loadFromFile("./NinjaAdventure/icons/E.png");
	E_button.setTexture(e_button);
	E_button.setScale(1, 1);
	E_button.setPosition(8570, 350);
	letter.loadFromFile("./NinjaAdventure/icons/OIP__2_-removebg-preview.png");
	Letter.setTexture(letter);
	Letter.setScale(1.5, 1.3);
	Letter.setPosition(8500, 600);
	letter_text[0].setFont(font);
	letter_text[0].setCharacterSize(20);
	letter_text[0].setPosition(8570, 650);
	letter_text[0].setString("CONGRATULATIONS");
	letter_text[0].setFillColor(Color::Black);
	letter_text[1].setFont(font);
	letter_text[1].setCharacterSize(20);
	letter_text[1].setPosition(8560, 720);
	letter_text[1].setString("TO   UNLOCK   LEVEL   2");
	letter_text[1].setFillColor(Color::Black);
	letter_text[2].setFont(font);
	letter_text[2].setCharacterSize(20);
	letter_text[2].setPosition(8580, 820);
	letter_text[2].setString("KEEP   IT   SECRET");
	letter_text[2].setFillColor(Color::Red);
	letter_text[3].setFont(font);
	letter_text[3].setCharacterSize(20);
	letter_text[3].setPosition(8560, 880);
	letter_text[3].setString("#FREE_PALESTINE");
	letter_text[3].setFillColor(Color::Black);
	letter_text[4].setFont(font);
	letter_text[4].setCharacterSize(20);
	letter_text[4].setPosition(8570, 760);
	letter_text[4].setString(" PRESS   [F8]   [F10]");
	letter_text[4].setFillColor(Color::Black);
	//-----------------------------
	sign_text[0].setFont(font);
	sign_text[0].setCharacterSize(40);
	sign_text[0].setPosition(5690, 825);
	sign_text[0].setString("0");
	sign_text[0].setFillColor(Color::Red);
	sign_text[1].setFont(font);
	sign_text[1].setCharacterSize(40);
	sign_text[1].setPosition(5690, 825);
	sign_text[1].setString("1");
	sign_text[1].setFillColor(Color::Red);
	sign_text[2].setFont(font);
	sign_text[2].setCharacterSize(40);
	sign_text[2].setPosition(5690, 825);
	sign_text[2].setString("2");
	sign_text[2].setFillColor(Color::Red);
	//----------------------
	clear.setFont(font);
	clear.setCharacterSize(60);
	clear.setPosition(6580, 700);
	clear.setString("CLEAR");
	clear.setFillColor(Color::Red);
	//heart
	heart.loadFromFile("./NinjaAdventure/icons/hearts.png");
	for (int i = 0; i < 3; i++)
	{
		hearts[i].setTexture(heart);
		hearts[i].setScale(.09f, .09f);
	}
	for (int i = 0; i < 3; i++)
	{
		hearts2[i].setTexture(heart);
		hearts2[i].setScale(.09f, .09f);
	}
	//game_over sprite
	game_over.loadFromFile("./NinjaAdventure/icons/game_over.png");
	Game_over.setTexture(game_over);
	name_player1.setFont(font);
	name_player1.setCharacterSize(20);
	name_player1.setString(name3);
	name_player1.setFillColor(Color(100, 50, 50));
	name_player2.setFont(font);
	name_player2.setCharacterSize(20);
	name_player2.setString(name4);
	name_player2.setFillColor(Color(100, 50, 50));
	//properties of pass_bg	
	pass_bg.setFillColor(Color(150, 0, 150));
	retry.setFont(font);
	retry.setString("RETRY");
	retry.setFillColor(Color::Red);
	retry.setCharacterSize(40);
	main_menu_text.setFont(font);
	main_menu_text.setString("MAIN    MENU");
	main_menu_text.setFillColor(Color::Red);
	main_menu_text.setCharacterSize(40);
	F_retry.setFont(font);
	F_retry.setString("RECOMMENCEZ");
	F_retry.setFillColor(Color::Red);
	F_retry.setCharacterSize(40);
	F_main.setFont(font);
	F_main.setString("MENU   PRINCIPAL");
	F_main.setFillColor(Color::Red);
	F_main.setCharacterSize(40);
	dooro.loadFromFile("opened_door.png");
	doorc.loadFromFile("closed_door.png");
	key.loadFromFile("key.png");
	Key.setTexture(key);
	Dooro.setTexture(dooro);
	Doorc.setTexture(doorc);
	Key.setScale(.15f, .15f);
	Key.setPosition(7425, 190);
	Doorc.setScale(0.3f, 0.3f);
	Dooro.setScale(0.71f, 0.71f);
	Doorc.setPosition(8650, 255);
	Dooro.setPosition(8650, 255);
	shift.loadFromFile("./NinjaAdventure/icons/shift.png");
	Shift.setTexture(shift);
	Shift.setPosition(8780, 230);
	Shift.setScale(.15, .15);
	quads[0].position = Vector2f(0, 0);
	quads[1].position = Vector2f(1920, 0);
	quads[2].position = Vector2f(0, 1080);
	quads[3].position = Vector2f(1920, 1080);
	quads[0].color = Color(50, 10, 50, 255);
	quads[1].color = Color(100, 20, 100, 255);
	quads[2].color = Color(100, 40, 100, 255);
	quads[3].color = Color(200, 80, 200, 255);
	pinkback.setSize(Vector2f(1920, 1080));
	pinkback.setFillColor(Color(50, 10, 50, 255));
	//properties of texts
	to_lvlsell.setFont(font);
	to_lvlsell.setString("To level select");
	to_lvlsell.setFillColor(Color::Red);
	to_lvlsell.setPosition(width / 3 + 110, 100);
	to_lvlsell.setCharacterSize(45);
	//--------------------------
	to_main.setFont(font);
	to_main.setString("To MAIN MENU");
	to_main.setFillColor(Color::Red);
	to_main.setPosition(width / 3 + 110, 100);
	to_main.setCharacterSize(45);
	//--------------------------
	fto_lvlsell.setFont(font);
	fto_lvlsell.setString("sélection de niveau");
	fto_lvlsell.setFillColor(Color::Red);
	fto_lvlsell.setPosition(width / 3 + 110, 100);
	fto_lvlsell.setCharacterSize(36);
	//--------------------------
	fto_main.setFont(font);
	fto_main.setString("menu principal");
	fto_main.setFillColor(Color::Red);
	fto_main.setPosition(width / 3 + 110, 100);
	fto_main.setCharacterSize(36);
	//--------------------------
	option.setFont(font);
	option.setString("OPTIONS");
	option.setFillColor(Color::Red);
	option.setPosition(width / 3 + 110, 100);
	option.setCharacterSize(70);
	//--------------------------
	edit_sound.setFont(font);
	edit_sound.setString("SOUND");
	edit_sound.setFillColor(Color::White);
	edit_sound.setOutlineThickness(1);
	edit_sound.setOutlineColor(Color::Black);
	edit_sound.setPosition(width / 3 + 100, 240);
	edit_sound.setCharacterSize(40);
	//--------------------------
	edit_music.setFont(font);
	edit_music.setString("MUSIC");
	edit_music.setFillColor(Color::White);
	edit_music.setOutlineThickness(1);
	edit_music.setOutlineColor(Color::Black);
	edit_music.setPosition(width / 3 + 100, 380);
	edit_music.setCharacterSize(40);
	//--------------------------
	language.setFont(font);
	language.setString("LANGUAGE");
	language.setFillColor(Color::White);
	language.setOutlineThickness(1);
	language.setOutlineColor(Color::Black);
	language.setPosition(width / 3 + 100, 500);
	language.setCharacterSize(40);
	//---------------------------
	back.setFont(font);
	back.setString("BACK");
	back.setFillColor(Color::White);
	back.setOutlineThickness(1);
	back.setOutlineColor(Color::Black);
	back.setPosition(width / 3 + 100, 620);
	back.setCharacterSize(40);
	//---------------------------
	choice_english.setFont(font);
	choice_english.setString("ENGLISH");
	choice_english.setFillColor(Color::Transparent);
	choice_english.setPosition(width / 3 + 170, 560);
	choice_english.setCharacterSize(40);
	//---------------------------
	choice_francais.setFont(font);
	choice_francais.setString("FRANÇAIS");
	choice_francais.setFillColor(Color::Transparent);
	choice_francais.setPosition(width / 3 + 160, 562);
	choice_francais.setCharacterSize(38);
	//properties of texts in french
	F_option.setFont(font);
	F_option.setString("PRAMÈTRES");
	F_option.setFillColor(Color::Red);
	F_option.setPosition(width / 3 + 80, 110);
	F_option.setCharacterSize(60);
	//---------------------------
	F_sound.setFont(font);
	F_sound.setString("SON");
	F_sound.setFillColor(Color::White);
	F_sound.setOutlineThickness(1);
	F_sound.setOutlineColor(Color::Black);
	F_sound.setPosition(width / 3 + 100, 240);
	F_sound.setCharacterSize(40);
	//----------------------------
	F_music.setFont(font);
	F_music.setString("MUSIQUE");
	F_music.setFillColor(Color::White);
	F_music.setOutlineThickness(1);
	F_music.setOutlineColor(Color::Black);
	F_music.setPosition(width / 3 + 100, 380);
	F_music.setCharacterSize(40);
	//---------------------------
	F_language.setFont(font);
	F_language.setString("LANGUE");
	F_language.setFillColor(Color::White);
	F_language.setOutlineThickness(1);
	F_language.setOutlineColor(Color::Black);
	F_language.setPosition(width / 3 + 100, 500);
	F_language.setCharacterSize(40);
	//--------------------------
	F_back.setFont(font);
	F_back.setString("DOS");
	F_back.setFillColor(Color::White);
	F_back.setOutlineThickness(1);
	F_back.setOutlineColor(Color::Black);
	F_back.setPosition(width / 3 + 100, 620);
	F_back.setCharacterSize(40);
	//properties of textbox
	text_box.loadFromFile("./NinjaAdventure/HUD/Dialog/DialogueBoxSimple.png");
	Text_box.setTexture(text_box);
	Text_box.setPosition(width / 3 + 80, 190);
	Text_box.setScale(1.3, 9);
	//icons
	//sound icons
	volume_icon[0].loadFromFile("./NinjaAdventure/icons/volume-up-interface-symbol.png");
	Volume_icon[0].setTexture(volume_icon[0]);
	Volume_icon[0].setPosition(width / 3 + 100, 300);
	Volume_icon[0].setScale(.1, .1);
	volume_icon[1].loadFromFile("./NinjaAdventure/icons/volume.png");
	Volume_icon[1].setTexture(volume_icon[1]);
	Volume_icon[1].setPosition(width / 3 + 100, 305);
	Volume_icon[1].setScale(.08, .08);
	volume_icon[2].loadFromFile("./NinjaAdventure/icons/mute.png");
	Volume_icon[2].setTexture(volume_icon[2]);
	Volume_icon[2].setPosition(width / 3 + 93, 305);
	Volume_icon[2].setScale(.08, .08);
	//music icons
	music_icon[0].loadFromFile("./NinjaAdventure/icons/quaver.png");
	Music_icon[0].setTexture(music_icon[0]);
	Music_icon[0].setPosition(width / 3 + 100, 440);
	Music_icon[0].setScale(.1, .1);
	music_icon[1].loadFromFile("./NinjaAdventure/icons/music.png");
	Music_icon[1].setTexture(music_icon[1]);
	Music_icon[1].setPosition(width / 3 + 100, 440);
	Music_icon[1].setScale(.1, .1);
	music_icon[2].loadFromFile("./NinjaAdventure/icons/mute_music.png");
	Music_icon[2].setTexture(music_icon[2]);
	Music_icon[2].setPosition(width / 3 + 100, 445);
	Music_icon[2].setScale(.09, .09);

	//arrows of changing language
	arrow1.setPosition(width / 3 + 430, 577);
	arrow1.setRotation(90);
	arrow1.setFillColor(Color::Black);
	//--------------------------
	arrow2.setPosition(width / 3 + 126, 597);
	arrow2.setRotation(270);
	arrow2.setFillColor(Color::Black);
	scroll_down(choose_option);
	//background
	Texture  backgroundTx;
	backgroundTx.loadFromFile("white.png");
	Sprite  background[2];
	for (int i = 0; i < 2; i++) {
		background[i].setTexture(backgroundTx);
		background[i].setPosition(Vector2f(i * 1920, 0));
		background[i].setScale(500, 500);
	}
	//View
	View cameraView;
	cameraView.setSize(1920, 985);
	//Ground
	Texture Ground;
	Ground.loadFromFile("Ground.png");
	Sprite g[ng1];
	for (int i = 0; i < ng1; i++)
		g[i].setTexture(Ground);
	g[0].setPosition(0, 950);
	g[0].setScale(10, 5);
	g[1].setPosition(1500, 950);
	g[1].setScale(15, 5);
	g[2].setPosition(0, 0);
	g[2].setScale(1, 70);
	g[3].setPosition(5920, 500);
	g[3].setScale(5, 30);
	g[4].setPosition(2780, 810);
	g[4].setScale(5, 9);
	g[5].setPosition(3036, 710);
	g[5].setScale(3, 9);
	g[6].setPosition(4100, 950);
	g[6].setScale(19.22, 5);
	g[7].setPosition(5500, 900);
	g[7].setScale(3, 3);
	g[8].setPosition(0, 0);
	g[8].setScale(90, 1);
	g[9].setPosition(8900, 0);
	g[9].setScale(3, 70);
	g[10].setPosition(4100, 950);
	g[10].setScale(18, 5);
	g[11].setPosition(6580, 500);
	g[11].setScale(.7, 4);
	g[12].setPosition(6680, 500);
	g[12].setScale(.7, 4);
	g[13].setPosition(6780, 500);
	g[13].setScale(.7, 4);
	g[14].setPosition(6880, 500);
	g[14].setScale(.7, 4);
	g[15].setPosition(6980, 500);
	g[15].setScale(.7, 4);
	g[16].setPosition(7080, 500);
	g[16].setScale(.7, 4);
	g[17].setPosition(7180, 500);
	g[17].setScale(.7, 4);
	g[18].setPosition(7280, 500);
	g[18].setScale(.7, 4);
	g[19].setPosition(7380, 500);
	g[19].setScale(.7, 4);
	g[20].setPosition(7480, 500);
	g[20].setScale(.7, 4);
	g[21].setPosition(7580, 500);
	g[21].setScale(.7, 4);
	g[22].setPosition(7680, 500);
	g[22].setScale(.7, 4);
	g[23].setPosition(7780, 500);
	g[23].setScale(.7, 4);
	g[24].setPosition(7880, 500);
	g[24].setScale(.7, 4);
	g[25].setPosition(7980, 500);
	g[25].setScale(.7, 4);
	g[26].setPosition(8080, 500);
	g[26].setScale(.7, 4);
	g[27].setPosition(8180, 500);
	g[27].setScale(.7, 4);
	g[28].setPosition(8280, 500);
	g[28].setScale(.7, 4);
	g[29].setPosition(6880, 320);
	g[29].setScale(.7, 4);
	g[30].setPosition(7430, 320);
	g[30].setScale(.7, 4);
	g[31].setPosition(7930, 320);
	g[31].setScale(.7, 4);
	g[32].setPosition(8380, 500);
	g[32].setScale(5, 5);
	//Button
	const int nb = 1;
	Texture Button;
	Button.loadFromFile("Button.png");
	Sprite b[nb];
	for (int i = 0; i < nb; i++) {
		b[i].setTexture(Button);
		b[i].setTextureRect(IntRect(0, 0, 16, 16));
		b[i].setScale(10, 3);
	}
	b[0].setPosition(4400, 910);
	//Elevator	
	Texture Elevator;
	Elevator.loadFromFile("Elevator.png");
	Sprite e[ne1];
	//Sprites
	PLAYERNEEDS_1 player_1;
	PLAYERNEEDS_2 player_2;
	player_1.walk[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	player_1.walk[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_1.walk[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_1.walk[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_1.walk[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_1.walk[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	player_1.walk[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	player_1.walk[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	//----------------------------------------------
	player_1.jump[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	player_1.jump[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_1.jump[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_1.jump[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_1.jump[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_1.jump[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	player_1.jump[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	player_1.jump[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	//-----------------------------------
	player_1.idle[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	player_1.idle[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_1.idle[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_1.idle[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_1.idle[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_1.idle[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	player_1.idle[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	player_1.idle[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	//-----------------------------------
	player_1.dead[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	player_1.dead[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_1.dead[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_1.dead[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_1.dead[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_1.dead[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	player_1.dead[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	player_1.dead[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	//------------------------------------
	player_1.faceset[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	player_1.faceset[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_1.faceset[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_1.faceset[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_1.faceset[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_1.faceset[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	player_1.faceset[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	player_1.faceset[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	player_1.scale = 5;
	player_1.jumpheight = 150.0f;
	//------------------------------------
	for (int i = 0; i < 8; i++)
	{
		player[i].setTexture(player_1.jump[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		player_dead[i].setTexture(player_1.dead[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		faceset[i].setTexture(player_1.faceset[i]);
	}
	faceset[x].setScale(2, 1);
	player_dead[x].setScale(6, 5);
	player[x].setScale(player_1.scale, player_1.scale);
	player[x].setPosition(300, 200);
	player[x].setOrigin(8, 8);
	//-------------------------------------
	player_2.walk[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	player_2.walk[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_2.walk[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_2.walk[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	//-------------------------------------
	player_2.jump[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	player_2.jump[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_2.jump[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_2.jump[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	//-------------------------------------
	player_2.idle[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	player_2.idle[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_2.idle[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_2.idle[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	//-------------------------------------
	player_2.dead[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	player_2.dead[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_2.dead[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_2.dead[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	//-------------------------------------
	player_2.faceset[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	player_2.faceset[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_2.faceset[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_2.faceset[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	player_2.scale = 5;
	player_2.jumpheight = 150.0f;
	//-------------------------------------
	for (int i = 0; i < 4; i++)
	{
		player2[i].setTexture(player_2.jump[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		player2_dead[i].setTexture(player_2.dead[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		faceset2[i].setTexture(player_2.faceset[i]);
	}
	faceset2[x2].setScale(2, 1);
	player2_dead[x2].setScale(6, 5);
	player2[x2].setScale(player_2.scale, player_2.scale);
	player2[x2].setPosition(200, 200);
	player2[x2].setOrigin(8, 8);
	Clock animationclock[6];
	for (int i = 0; i < 6; i++)
	{
		animationclock[i].restart();
	}
	int idlex1 = 0, idlex2 = 0;
	int righty1 = 0, righty2 = 0;
	int lefty1 = 0, lefty2 = 0;
	bool jumped = 0, jumped2 = 0, isAbove1 = 0, isAbove2 = 0;
	while (window.isOpen())
	{
		Event event;
		gameclock.restart();
		gameclock2.restart();
		name_player1.setPosition(player[x].getPosition().x - name_player1.getGlobalBounds().width / 2, player[x].getPosition().y - 100);
		name_player2.setPosition(player2[x2].getPosition().x - name_player2.getGlobalBounds().width / 2, player2[x2].getPosition().y - 100);
		pass_bg.setPosition(viewxcalc - window.getSize().x / 2.0, 0);
		retry.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0, pass_bg.getSize().y / 2.0 + 80);
		main_menu_text.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 50, pass_bg.getSize().y / 2.0 + 200);
		F_retry.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 100, pass_bg.getSize().y / 2.0 + 80);
		F_main.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 130, pass_bg.getSize().y / 2.0 + 200);
		Game_over.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 180, pass_bg.getSize().y / 2.0 - 250);
		player_dead[x].setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 + 20, pass_bg.getSize().y / 2.0 - 250);
		player2_dead[x2].setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 + 20, pass_bg.getSize().y / 2.0 - 250);
		for (int i = 0; i < 3; i++)
			hearts[i].setPosition(viewxcalc - 870 + 50 * i, window.getSize().y / 10.0);
		for (int i = 0; i < 3; i++)
			hearts2[i].setPosition(viewxcalc - 870 + 50 * i, window.getSize().y / 20.0);
		faceset[x].setPosition(viewxcalc - window.getSize().x / 2.0, window.getSize().y / 10.0);
		faceset2[x2].setPosition(viewxcalc - window.getSize().x / 2.0, window.getSize().y / 20.0);
		pinkback.setPosition(viewxcalc - veiwcom, 0);
		quads[0].position = Vector2f(viewxcalc - veiwcom, 0);
		quads[1].position = Vector2f(viewxcalc + 1920 - veiwcom, 0);
		quads[2].position = Vector2f(viewxcalc - veiwcom, 1080);
		quads[3].position = Vector2f(viewxcalc + 1920 - veiwcom, 1080);
		option.setPosition(viewxcalc + 1920 / 3.f + 110 - veiwcom, 100);
		edit_sound.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 240);
		edit_music.setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 240);
		language.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 500);
		back.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 620);
		choice_english.setPosition(viewxcalc + 1920 / 3.f + 170 - veiwcom, 560);
		choice_francais.setPosition(viewxcalc + 1920 / 3.f + 160 - veiwcom, 562);
		F_option.setPosition(viewxcalc + 1920 / 3.f + 80 - veiwcom, 110);
		F_sound.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 240);
		F_music.setPosition(viewxcalc + 1920 / 3.f + 240 - veiwcom, 240);
		F_language.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 500);
		F_back.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 620);
		Text_box.setPosition(viewxcalc + 1920 / 3.f + 80 - veiwcom, 190);
		Volume_icon[0].setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 300);
		Volume_icon[1].setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 305);
		Volume_icon[2].setPosition(viewxcalc + 1920 / 3.f + 93 - veiwcom, 305);
		Music_icon[0].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
		Music_icon[1].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
		Music_icon[2].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
		arrow1.setPosition(viewxcalc + 1920 / 3.f + 430 - veiwcom, 577);
		arrow2.setPosition(viewxcalc + 1920 / 3.f + 126 - veiwcom, 597);
		to_lvlsell.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 360);
		to_main.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 430);
		fto_lvlsell.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 360);
		fto_main.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 430);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if ((Keyboard::isKeyPressed(Keyboard::Escape) && !previousbutton1) || (back_isselected() && Keyboard::isKeyPressed(Keyboard::Return) && !previousbutton2)) {
				if (!failed1 && !failed2 && !complete) {
					pause_unpause(gamecontrol);
					lang_update_anima();
				}
			}
			if (failed1 || failed2 || complete) {
				if (!gamecontrol)
					pause_unpause(gamecontrol);
			}
			previousbutton1 = Keyboard::isKeyPressed(Keyboard::Escape);
			previousbutton2 = Keyboard::isKeyPressed(Keyboard::Return);

			if (Keyboard::isKeyPressed(Keyboard::D) && !gamecontrol) {
				if (!gamecontrol) {
					turnup_sound(choose_option, cnt_volume_wasd);
					if (cnt_music != 4)
						turnup_music(choose_option, cnt_music);
					lang_right(cnt_language);
					lang_update_anima();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::A) && !gamecontrol) {
				if (!gamecontrol) {
					turndown_sound(choose_option, cnt_volume_wasd);
					turndown_music(choose_option, cnt_music);
					lang_right(cnt_language);
					lang_update_anima();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::W) && !gamecontrol && !previousbutton3) {
				if (!gamecontrol) {
					scroll_up(choose_option);
					lang_update_anima();
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::S) && !gamecontrol && !previousbutton4) {
				scroll_down(choose_option);
				lang_update_anima();

			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && !gamecontrol && main_isselected()) {
				pause_unpause(gamecontrol);
				music.stop();
				cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
				cameraView.setSize(window.getSize().x, window.getSize().y);
				window.setView(cameraView);
				main_menu();
				beginning = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && !gamecontrol && select_isselected()) {
				pause_unpause(gamecontrol);
				music.stop();
				cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
				cameraView.setSize(window.getSize().x, window.getSize().y);
				window.setView(cameraView);
				level_select(type_language, music_Volume, name1, name2);
			}
			previousbutton3 = Keyboard::isKeyPressed(Keyboard::W);
			previousbutton4 = Keyboard::isKeyPressed(Keyboard::S);
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				selector = (selector + 1) % 4;
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				selector--;
				if (selector < 0)
					selector = 3;
			}
			if ((selector == 0 || selector == 1) && Keyboard::isKeyPressed(Keyboard::Enter) && (failed1 || failed2))
			{
				music.stop();
				level1();
			}
			if ((selector == 2 || selector == 3) && Keyboard::isKeyPressed(Keyboard::Enter) && (failed1 || failed2))
			{
				music.stop();
				cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
				cameraView.setSize(window.getSize().x, window.getSize().y);
				window.setView(cameraView);
				beginning = true;
				main();
			}
			if (player[x].getGlobalBounds().intersects(sign[1].getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(sign[1].getGlobalBounds()))
				if (Keyboard::isKeyPressed(Keyboard::E))
					letter_opened = true;
				else if (player[x].getGlobalBounds().intersects(sign[1].getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(sign[1].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Escape))
					letter_opened = false;
		}
		viewdeltax = abs(player[x].getPosition().x - player2[x2].getPosition().x);
		if (viewdeltax >= (window.getSize().x - player_1.idle[x].getSize().x)) {//player1 arrows ; player2 wasd
			extreme_x = 1; //can be used to pause calculation of viewxcalc for optimisation
		}
		else {
			extreme_x = 0;
		}
		if (extreme_x)
		{
			if (player[x].getPosition().x > player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::A))
					player2[x2].move(7, 0);//or player2.move(-7,0);
				player[x].move(-7, 0);//or player1.move(7,0);
			}
			else if (player[x].getPosition().x > player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::Right))
					player[x].move(-7, 0);//or player2.move(-7,0);
				player2[x2].move(7, 0);//or player2.move(-7,0);
			}
			if (player[x].getPosition().x < player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::Left))
					player[x].move(7, 0);//or player1.move(-7,0);
				player2[x2].move(-7, 0);//or player2.move(7,0);
			}
			else if (player[x].getPosition().x < player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::A))
					player2[x2].move(-7, 0);//or player1.move(-7,0);
				player[x].move(7, 0);//or player2.move(-7,0);
			}
		}
		if (player2[x2].getGlobalBounds().intersects(Key.getGlobalBounds()) && keyfree) {
			col_key.play();
			keyfree = 0;
			keyplayer = 1;
		}
		if (player[x].getGlobalBounds().intersects(Key.getGlobalBounds()) && keyfree) {
			col_key.play();
			keyfree = 0;
			keyplayer = 0;
		}
		if (!keyplayer && !keyfree) {

			Key.setPosition(player[x].getPosition().x - 100, player[x].getPosition().y - 100);
		}
		if (keyplayer && !keyfree) {
			Key.setPosition(player2[x2].getPosition().x - 100, player2[x2].getPosition().y - 100);
		}
		if ((player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && !keyfree && !keyplayer) {

			Key.setScale(0, 0);
			endstage = 1;
		}
		if ((player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && !keyfree && keyplayer) {

			Key.setScale(0, 0);
			endstage = 1;
		}
		if (endstage) {
			openess = 1;
		}
		else {
			openess = 0;
		}
		if ((player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && openess) {
			pause1 = 0;
		}
		if ((player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && openess) {
			pause2 = 0;
		}
		if (player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds()) && openess && (player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds()))) {
			complete = 1;
		}
		if (selector == 0 || selector == 1)
		{
			retry.setFillColor(Color::Red);
			F_retry.setFillColor(Color::Red);
		}
		else
		{
			retry.setFillColor(Color::White);
			F_retry.setFillColor(Color::White);
		}
		if (selector == 2 || selector == 3)
		{
			main_menu_text.setFillColor(Color::Red);
			F_main.setFillColor(Color::Red);
		}
		else
		{
			main_menu_text.setFillColor(Color::White);
			F_main.setFillColor(Color::White);
		}

		if (animationclock[0].getElapsedTime().asSeconds() >= 0.08) {
			for (int i = 0; i < 8; i++)
			{
				player[i].setTexture(player_1.idle[i]);
			}
			player[x].setTextureRect(IntRect(0, 0, 16, 16));
			/*player.setTextureRect(IntRect(idlex1 * 16, 0, 16, 16));
			idlex1++;
			idlex1 %= 4;*/
			animationclock[0].restart();
		}
		if (animationclock[3].getElapsedTime().asSeconds() >= 0.08) {
			for (int i = 0; i < 4; i++)
			{
				player2[i].setTexture(player_2.idle[i]);
			}
			player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
			/*player2.setTextureRect(IntRect(idlex2 * 16, 0, 16, 16));
			idlex2++;
			idlex2 %= 4;*/
			animationclock[3].restart();
		}
		//WHEN UNCOMMENTED, PLAYER REVOLVES AROUND HIMSELF 
		//PLAYER MOVEMENT
		//----------------------------------------------------------------------------------------------------------
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !ending1 && gamecontrol)
		{
			player[x].setScale(player_1.scale, player_1.scale);
			player[x].move(7, 0);
			for (int i = 0; i < 8; i++)
				player[i].setTexture(player_1.walk[i]);
			player[x].setTextureRect(IntRect(3 * 16, righty1 * 16, 16, 16));
			if (animationclock[1].getElapsedTime().asSeconds() >= 0.08) {
				righty1++;
				righty1 %= 4;
				animationclock[1].restart();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D) && !ending2 && gamecontrol)
		{
			player2[x2].setScale(player_2.scale, player_2.scale);
			player2[x2].move(7, 0);
			for (int i = 0; i < 4; i++)
				player2[i].setTexture(player_2.walk[i]);
			player2[x2].setTextureRect(IntRect(3 * 16, righty2 * 16, 16, 16));
			if (animationclock[4].getElapsedTime().asSeconds() >= 0.08) {

				righty2++;
				righty2 %= 4;
				animationclock[4].restart();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !ending1 && gamecontrol)
		{
			player[x].setScale(player_1.scale, player_1.scale);
			player[x].move(-7, 0);
			for (int i = 0; i < 8; i++)
				player[i].setTexture(player_1.walk[i]);
			player[x].setTextureRect(IntRect(2 * 16, lefty1 * 16, 16, 16));
			if (animationclock[1].getElapsedTime().asSeconds() >= 0.08) {

				lefty1++;
				lefty1 %= 4;
				animationclock[1].restart();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A) && !ending2 && gamecontrol)
		{
			player2[x2].setScale(player_2.scale, player_2.scale);
			player2[x2].move(-7, 0);
			for (int i = 0; i < 4; i++)
				player2[i].setTexture(player_2.walk[i]);
			player2[x2].setTextureRect(IntRect(2 * 16, lefty2 * 16, 16, 16));
			if (animationclock[4].getElapsedTime().asSeconds() >= 0.08) {

				lefty2++;
				lefty2 %= 4;
				animationclock[4].restart();
			}
		}
		//collision with X
		for (int i = 0; i < ng1; i++)
		{
			if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Right) && g[i].getPosition().y < player[x].getPosition().y && !ending1)
			{
				if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
					player[x].move(-1, 0);
				player[x].move(-10, 0);
			}
			if (player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::D) && g[i].getPosition().y < player2[x2].getPosition().y && !ending2)
			{
				if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
					player[x].move(-1, 0);
				player2[x2].move(-10, 0);
			}
			if (player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::A) && g[i].getPosition().y < player2[x2].getPosition().y && !ending2)
			{
				if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
					player[x].move(-1, 0);
				player2[x2].move(10, 0);
			}
			if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Left) && g[i].getPosition().y < player[x].getPosition().y && !ending1)
			{
				if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
					player[x].move(-1, 0);
				player[x].move(10, 0);
			}
		}
		//JUMP AND GRAVITY
		//==================================================================================================================
		//Player 1
		//-------------------
		if ((!isGrounded_level1(player[x], g)) && !jumped && !isAbove1)
		{
			for (int i = 0; i < 8; i++)
				player[i].setTexture(player_1.jump[i]); //fall
			player[x].setTextureRect(IntRect(0, 0, 16, 16));
			//player.move(0, animationclk3.getElapsedTime().asSeconds()); WHEN UNCOMMENTED, PLAYER MOVES UP AND DOWN WHEN ON TOP OF THE OTHER PLAYER INSTEAD OF STAYING STILL
			player[x].move(0, 7);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !jumped && !ending1 && gamecontrol)
			{
				jumped = 1;
				player_1.startposition = player[x].getPosition().y;
				animationclock[2].restart();
				jump.play();
			}
		}
		if (jumped)
		{
			for (int i = 0; i < 8; i++)
				player[i].setTexture(player_1.jump[i]);
			if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			{
				player[x].setTextureRect(IntRect(2 * 16, 0, 16, 16));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			{

				player[x].setTextureRect(IntRect(3 * 16, 0, 16, 16));
			}
			else
			{
				player[x].setTextureRect(IntRect(0 * 16, 0, 16, 16));
			}
			player[x].move(0, -7);
			if (player_1.startposition - player[x].getPosition().y >= player_1.jumpheight) {
				jumped = 0;
				animationclock[2].restart();
			}
		}
		//Player 2
		//-------------------
		if ((!isGrounded_level1(player2[x2], g)) && !jumped2 && !isAbove2) //to fall down at first
		{
			for (int i = 0; i < 4; i++)
				player2[i].setTexture(player_2.jump[i]);
			player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
			//player2.move(0, animation2clk3.getElapsedTime().asSeconds() * 7); //WHEN UNCOMMENTED, PLAYER MOVES UP AND DOWN WHEN ON TOP OF THE OTHER PLAYER INSTEAD OF STAYING STILL
			player2[x2].move(0, 7);

		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::W) && !jumped2 && !ending2 && gamecontrol)
			{
				jumped2 = 1;
				player_2.startposition = player2[x2].getPosition().y;
				animationclock[5].restart();
				jump.play();
			}
		}
		if (jumped2)

		{
			for (int i = 0; i < 4; i++)
				player2[i].setTexture(player_2.jump[i]);
			if (Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				player2[x2].setTextureRect(IntRect(2 * 16, 0, 16, 16));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				player2[x2].setTextureRect(IntRect(3 * 16, 0, 16, 16));
			}
			else
			{
				player2[x2].setTextureRect(IntRect(0 * 16, 0, 16, 16));
			}

			player2[x2].move(0, -7);
			if (player_2.startposition - player2[x2].getPosition().y >= player_2.jumpheight)
			{
				jumped2 = 0;
				animationclock[5].restart();
			}
		}
		//PLAYER COLLISON 
		//----------------------------------------------------------------------------------------------------------------------
		if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && ((player[x].getPosition().y > player2[x2].getPosition().y) || (player[x].getPosition().y < player2[x2].getPosition().y)))
		{
			if (player[x].getPosition().y < player2[x2].getPosition().y)
			{
				player[x].setTexture(player_1.idle[x]);
				player[x].setTextureRect(IntRect(0, 0, 16, 16));
				player[x].move(0, -7);
				isAbove1 = 1;
			}
			else if (player[x].getPosition().y > player2[x2].getPosition().y) {
				player2[x2].setTexture(player_2.idle[x2]);
				player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
				player2[x2].move(0, -7);
				isAbove2 = 1;
			}
		}
		else
		{
			isAbove1 = 0; isAbove2 = 0;
			if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Left) && !ending1)
			{
				player[x].move(7, 0);

			}
			if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Right) && !ending1)
			{
				player[x].move(-7, 0);
			}

			if (player2[x2].getGlobalBounds().intersects(player[x].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::A) && !ending2)
			{
				player2[x2].move(7, 0);

			}

			if (player2[x2].getGlobalBounds().intersects(player[x].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::D) && !ending2)
			{
				player2[x2].move(-7, 0);
			}

		}
		//Button
		if ((player[x].getGlobalBounds().intersects(b[0].getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(b[0].getGlobalBounds()))&&!button_sound)
		{
			b[0].setTextureRect(IntRect(16, 0, 32, 16));
			button_pressed = true;
			button_sound = true;
		}
		if (button_pressed)
		{
			if (g[10].getPosition().x > 2000)
				g[10].move(-15, 0);
		}
		if (counter_fail_1 == 0)
		{
			failed1 = true;
		}
		if (counter_fail_2 == 0)
		{
			failed2 = true;
		}
		if (player[x].getPosition().y > 1200 && player[x].getPosition().y < 1210 || player2[x2].getPosition().y > 1200 && player2[x2].getPosition().y < 1210)
		{
			fall.play();
		}
		if (player[x].getPosition().y > 1500 && !checked)
		{
			if (player2[x2].getPosition().x <= 300)
			{
				player[x].setPosition(player2[x2].getPosition().x + 100, 300);
				counter_fail_1--;
			}
			else
			{
				player[x].setPosition(player[x].getPosition().x - 100, 300);
				counter_fail_1--;
			}
		}
		if (player2[x2].getPosition().y > 1500 && !checked)
		{
			if (player[x].getPosition().x <= 300)
			{
				player2[x2].setPosition(player[x].getPosition().x + 100, 300);
				counter_fail_2--;
			}
			else
			{
				player2[x2].setPosition(player[x].getPosition().x - 100, 300);
				counter_fail_2--;
			}
		}
		else if (player[x].getPosition().y > 1500 && checked)
		{
			player[x].setPosition(6000, 200);
			player2[x2].setPosition(6100, 200);
			for (int i = 11; i < 29; i++)
				g[i].setPosition(6580 + (i - 11) * 100, 500);
			for (int i = 0; i < 29; i++)
				fallen[i] = false;
			openess = false;
			keyfree = 1;
			keyplayer = 0;
			endstage = 0;
			complete = 0;
			pause1 = 1;
			pause2 = 1;
			Key.setPosition(7425, 190);
			Key.setScale(.15f, .15f);
			ending1 = false;
			ending2 = false;
			counter_fail_1--;
		}
		else if (player2[x2].getPosition().y > 1500 && checked)
		{
			player[x].setPosition(6000, 200);
			player2[x2].setPosition(6100, 200);
			for (int i = 11; i < 29; i++)
				g[i].setPosition(6580 + (i - 11) * 100, 500);
			for (int i = 0; i < 29; i++)
				fallen[i] = false;
			openess = false;
			keyfree = 1;
			keyplayer = 0;
			endstage = 0;
			complete = 0;
			pause1 = 1;
			pause2 = 1;
			Key.setPosition(7425, 190);
			Key.setScale(.15f, .15f);
			counter_fail_2--;
			ending1 = false;
			ending2 = false;
		}
		if (timer < 3)
		{
			cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
			window.setView(cameraView);
			is_int = 1;
		}
		else
		{
			is_int = 0;
			viewxcalc = (player[x].getPosition().x + player2[x2].getPosition().x) / 2.f;//before window.clear
			if (viewxcalc < 1000)
				viewxcalc = 1000;
			if (viewxcalc > 8000)
				viewxcalc = 8000;
			cameraView.setCenter(viewxcalc, window.getSize().y - 495);
		}
		if (player[x].getGlobalBounds().intersects(g[7].getGlobalBounds()) && player2[x2].getGlobalBounds().intersects(g[7].getGlobalBounds()) && g[7].getPosition().y >= 500 && gamecontrol)
		{
			g[7].move(0, -2);
			player[x].move(0, -2);
			player2[x2].move(0, -2);
			sign[0].move(0, -2);
			for (int i = 0; i < 3; i++)
				sign_text[i].move(0, -2);
		}
		else if ((!player[x].getGlobalBounds().intersects(g[7].getGlobalBounds()) || !player2[x2].getGlobalBounds().intersects(g[7].getGlobalBounds())) && g[7].getPosition().y <= 900 && gamecontrol)
		{
			g[7].move(0, 2);
			if (player[x].getGlobalBounds().intersects(g[7].getGlobalBounds()))
				player[x].move(0, 2);
			if (player2[x2].getGlobalBounds().intersects(g[7].getGlobalBounds()))
				player2[x2].move(0, 2);
			sign[0].move(0, 2);
			for (int i = 0; i < 3; i++)
				sign_text[i].move(0, 2);
		}
		if (player[x].getPosition().y >= g[7].getPosition().y && player[x].getPosition().x > 5500 && gamecontrol)
		{
			player[x].move(0, -.1);
			if (player[x].getGlobalBounds().intersects(g[7].getGlobalBounds()))
			{
				fall.play();
				player[x].setPosition(5400, 800);
				counter_fail_1--;
			}
		}
		if (player2[x2].getPosition().y >= g[7].getPosition().y && player2[x2].getPosition().x > 5500 && gamecontrol)
		{
			player2[x2].move(0, -.1);
			if (player2[x2].getGlobalBounds().intersects(g[7].getGlobalBounds()))
			{
				fall.play();
				player2[x2].setPosition(5400, 800);
				counter_fail_2--;
			}
		}
		if (player[x].getGlobalBounds().intersects(Flag.getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(Flag.getGlobalBounds()))
		{
			checked = true;
		}
		for (int i = 11; i < 29; i++)
		{
			if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()))
				fallen[i] = true;
			if (fallen[i])
			{
				if (g[i].getPosition().y >= 530)
					g[i].move(0, 10);
				else
					g[i].move(0, 2);
			}
		}
		if (!ending1 && player[x].getGlobalBounds().intersects(Dooro.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::RShift) && openess)
			ending1 = true;
		else if (ending1 && Keyboard::isKeyPressed(Keyboard::Key::RShift) && !ending2)
			ending1 = false;
		if (!ending2 && player2[x2].getGlobalBounds().intersects(Dooro.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::LShift) && openess)
			ending2 = true;
		else if (ending2 && Keyboard::isKeyPressed(Keyboard::Key::LShift) && !ending1)
			ending2 = false;
		window.setView(cameraView);
		window.clear();
		if (timer2 > 5)
		{
			Pass2 = true;
			level2();
		}
		for (int i = 0; i < 2; i++)
			window.draw(background[i]);
		//Draw Map
		window.draw(sign[0]);
		if (player[x].getGlobalBounds().intersects(g[7].getGlobalBounds()) && player2[x2].getGlobalBounds().intersects(g[7].getGlobalBounds()))
			window.draw(sign_text[0]);
		else if (!(player[x].getGlobalBounds().intersects(g[7].getGlobalBounds())) && !(player2[x2].getGlobalBounds().intersects(g[7].getGlobalBounds())))
		{

			window.draw(sign_text[2]);
		}
		else
			window.draw(sign_text[1]);
		window.draw(Flag);
		window.draw(sign[1]);
		for (int i = 0; i < ng1; i++)
			window.draw(g[i]);
		window.draw(b[0]);
		window.draw(Key);
		if (openess) {
			window.draw(Dooro);
		}
		else
			window.draw(Doorc);
		if (checked)
			window.draw(check);
		if (player[x].getGlobalBounds().intersects(sign[1].getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(sign[1].getGlobalBounds()))
			window.draw(E_button);
		if (!ending1)
		{
			window.draw(player[x]);
			player[x].setScale(5, 5);
		}
		else
			player[x].setScale(.1, .1);
		if (!ending2)
		{
			window.draw(player2[x2]);
			player2[x2].setScale(5, 5);
		}
		else
			player2[x2].setScale(.1, .1);
		if (!ending1)
			window.draw(name_player1);
		if (!ending2)
			window.draw(name_player2);
		if (!is_int)
		{
			for (int i = 0; i < counter_fail_1; i++)
				window.draw(hearts[i]);
			for (int i = 0; i < counter_fail_2; i++)
				window.draw(hearts2[i]);
			window.draw(faceset[x]);
			window.draw(faceset2[x2]);
		}
		embeddeddraw_intro_lvl1();
		if (letter_opened)
		{
			window.draw(Letter);
			for (int i = 0; i < 5; i++)
				window.draw(letter_text[i]);
		}
		if (ending1 && ending2)
		{
			music.stop();
			window.draw(clear);
			if (clear.getPosition().x <= 7900)
				clear.move(20, 0);
			else
				to_next = true;
		}
		if ((player[x].getGlobalBounds().intersects(Dooro.getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(Dooro.getGlobalBounds())) && !ending1 && !ending2)
			window.draw(Shift);
		if (cnt_music == 0)
			music.stop();
		else if (cnt_music == 1)
		{
			music.play();
			cnt_music = 4;
			music.setVolume(music_Volume * cnt_music);
		}
		jump.setVolume(sound_volume * cnt_volume_wasd);
		fall.setVolume(sound_volume * cnt_volume_wasd);
		col_key.setVolume(sound_volume * cnt_volume_wasd);
		embedded_draw_pause();
		if (failed1 || failed2)
		{
			music.stop();
			window.draw(pass_bg);
			if (!type_language)
			{
				window.draw(retry);
				window.draw(main_menu_text);
			}
			else
			{
				window.draw(F_retry);
				window.draw(F_main);
			}
			window.draw(Game_over);
			if (counter_fail_1 == 0)
				window.draw(player_dead[x]);
			if (counter_fail_2 == 0)
				window.draw(player2_dead[x2]);
		}
		window.display();
		timer += gameclock.getElapsedTime().asSeconds();
		if (to_next)
			timer2 += gameclock2.getElapsedTime().asSeconds();
	}
}
void level2()
{
	timer = 0;
	window.setFramerateLimit(60);
	const float width = 1920;
	Texture back_ground, left_icon, right_icon, right_icon2, left_icon2, text_box, volume_icon[3] = {}
	, music_icon[3] = {}, heart, sign, e_button, letter, shift;
	Sprite player[8], player2[4], Block1, Block2, Dooro, Doorc, Key, Spike, Game_over,
		player_dead[8], player2_dead[4], hearts[3], hearts2[3], faceset[8], faceset2[4], Sign, E_button, Letter, Shift;
	Music jump, fall, music, col_key;
	int selector = 0;
	bool to_next = 0, next = 0, is_int = 0;
	Clock gameclock2;
	float timer2 = 0;
	Text clear;
	lvl2_intro(1920, 1080);
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	letter.loadFromFile("./NinjaAdventure/icons/OIP__2_-removebg-preview.png");
	e_button.loadFromFile("./NinjaAdventure/icons/E.png");
	E_button.setTexture(e_button);
	E_button.setScale(1, 1);
	sign.loadFromFile("./NinjaAdventure/icons/sign.png");
	col_key.openFromFile("././NinjaAdventure/Sounds/Game/Coin.wav");
	music.openFromFile("./NinjaAdventure/Musics/28 - Tension.ogg");
	music.setLoop(true);
	music.play();
	fall.openFromFile("./NinjaAdventure/Sounds/Game/Kill.wav");
	jump.openFromFile("./NinjaAdventure/Sounds/Game/Jump.wav");
	quads[0].position = Vector2f(0, 0);
	quads[1].position = Vector2f(1920, 0);
	quads[2].position = Vector2f(0, 1080);
	quads[3].position = Vector2f(1920, 1080);
	quads[0].color = Color(50, 10, 50, 255);
	quads[1].color = Color(100, 20, 100, 255);
	quads[2].color = Color(100, 40, 100, 255);
	quads[3].color = Color(200, 80, 200, 255);
	pinkback.setSize(Vector2f(1920, 1080));
	pinkback.setFillColor(Color(50, 10, 50, 255));
	//properties of texts
	to_lvlsell.setFont(font);
	to_lvlsell.setString("To level select");
	to_lvlsell.setFillColor(Color::Red);
	to_lvlsell.setPosition(width / 3 + 110, 100);
	to_lvlsell.setCharacterSize(45);
	//--------------------------
	to_main.setFont(font);
	to_main.setString("To MAIN MENU");
	to_main.setFillColor(Color::Red);
	to_main.setPosition(width / 3 + 110, 100);
	to_main.setCharacterSize(45);
	//--------------------------
	fto_lvlsell.setFont(font);
	fto_lvlsell.setString("sélection de niveau");
	fto_lvlsell.setFillColor(Color::Red);
	fto_lvlsell.setPosition(width / 3 + 110, 100);
	fto_lvlsell.setCharacterSize(36);
	//--------------------------
	fto_main.setFont(font);
	fto_main.setString("menu principal");
	fto_main.setFillColor(Color::Red);
	fto_main.setPosition(width / 3 + 110, 100);
	fto_main.setCharacterSize(36);
	//--------------------------
	option.setFont(font);
	option.setString("OPTIONS");
	option.setFillColor(Color::Red);
	option.setPosition(width / 3 + 110, 100);
	option.setCharacterSize(70);
	//--------------------------
	edit_sound.setFont(font);
	edit_sound.setString("SOUND");
	edit_sound.setFillColor(Color::White);
	edit_sound.setOutlineThickness(1);
	edit_sound.setOutlineColor(Color::Black);
	edit_sound.setPosition(width / 3 + 100, 240);
	edit_sound.setCharacterSize(40);
	//--------------------------
	edit_music.setFont(font);
	edit_music.setString("MUSIC");
	edit_music.setFillColor(Color::White);
	edit_music.setOutlineThickness(1);
	edit_music.setOutlineColor(Color::Black);
	edit_music.setPosition(width / 3 + 100, 380);
	edit_music.setCharacterSize(40);
	//--------------------------
	language.setFont(font);
	language.setString("LANGUAGE");
	language.setFillColor(Color::White);
	language.setOutlineThickness(1);
	language.setOutlineColor(Color::Black);
	language.setPosition(width / 3 + 100, 500);
	language.setCharacterSize(40);
	//---------------------------
	back.setFont(font);
	back.setString("BACK");
	back.setFillColor(Color::White);
	back.setOutlineThickness(1);
	back.setOutlineColor(Color::Black);
	back.setPosition(width / 3 + 100, 620);
	back.setCharacterSize(40);
	//---------------------------
	choice_english.setFont(font);
	choice_english.setString("ENGLISH");
	choice_english.setFillColor(Color::Transparent);
	choice_english.setPosition(width / 3 + 170, 560);
	choice_english.setCharacterSize(40);
	//---------------------------
	choice_francais.setFont(font);
	choice_francais.setString("FRANÇAIS");
	choice_francais.setFillColor(Color::Transparent);
	choice_francais.setPosition(width / 3 + 160, 562);
	choice_francais.setCharacterSize(38);
	//properties of texts in french
	F_option.setFont(font);
	F_option.setString("PRAMÈTRES");
	F_option.setFillColor(Color::Red);
	F_option.setPosition(width / 3 + 80, 110);
	F_option.setCharacterSize(60);
	//---------------------------
	F_sound.setFont(font);
	F_sound.setString("SON");
	F_sound.setFillColor(Color::White);
	F_sound.setOutlineThickness(1);
	F_sound.setOutlineColor(Color::Black);
	F_sound.setPosition(width / 3 + 100, 240);
	F_sound.setCharacterSize(40);
	//----------------------------
	F_music.setFont(font);
	F_music.setString("MUSIQUE");
	F_music.setFillColor(Color::White);
	F_music.setOutlineThickness(1);
	F_music.setOutlineColor(Color::Black);
	F_music.setPosition(width / 3 + 100, 380);
	F_music.setCharacterSize(40);
	//---------------------------
	F_language.setFont(font);
	F_language.setString("LANGUE");
	F_language.setFillColor(Color::White);
	F_language.setOutlineThickness(1);
	F_language.setOutlineColor(Color::Black);
	F_language.setPosition(width / 3 + 100, 500);
	F_language.setCharacterSize(40);
	//--------------------------
	F_back.setFont(font);
	F_back.setString("DOS");
	F_back.setFillColor(Color::White);
	F_back.setOutlineThickness(1);
	F_back.setOutlineColor(Color::Black);
	F_back.setPosition(width / 3 + 100, 620);
	F_back.setCharacterSize(40);
	//properties of textbox
	text_box.loadFromFile("./NinjaAdventure/HUD/Dialog/DialogueBoxSimple.png");
	Text_box.setTexture(text_box);
	Text_box.setPosition(width / 3 + 80, 190);
	Text_box.setScale(1.3, 9);
	//icons
	//sound icons
	volume_icon[0].loadFromFile("./NinjaAdventure/icons/volume-up-interface-symbol.png");
	Volume_icon[0].setTexture(volume_icon[0]);
	Volume_icon[0].setPosition(width / 3 + 100, 300);
	Volume_icon[0].setScale(.1, .1);
	volume_icon[1].loadFromFile("./NinjaAdventure/icons/volume.png");
	Volume_icon[1].setTexture(volume_icon[1]);
	Volume_icon[1].setPosition(width / 3 + 100, 305);
	Volume_icon[1].setScale(.08, .08);
	volume_icon[2].loadFromFile("./NinjaAdventure/icons/mute.png");
	Volume_icon[2].setTexture(volume_icon[2]);
	Volume_icon[2].setPosition(width / 3 + 93, 305);
	Volume_icon[2].setScale(.08, .08);
	//music icons
	music_icon[0].loadFromFile("./NinjaAdventure/icons/quaver.png");
	Music_icon[0].setTexture(music_icon[0]);
	Music_icon[0].setPosition(width / 3 + 100, 440);
	Music_icon[0].setScale(.1, .1);
	music_icon[1].loadFromFile("./NinjaAdventure/icons/music.png");
	Music_icon[1].setTexture(music_icon[1]);
	Music_icon[1].setPosition(width / 3 + 100, 440);
	Music_icon[1].setScale(.1, .1);
	music_icon[2].loadFromFile("./NinjaAdventure/icons/mute_music.png");
	Music_icon[2].setTexture(music_icon[2]);
	Music_icon[2].setPosition(width / 3 + 100, 445);
	Music_icon[2].setScale(.09, .09);
	shift.loadFromFile("./NinjaAdventure/icons/shift.png");
	Shift.setTexture(shift);
	Shift.setPosition(4390, 575);
	Shift.setScale(.15, .15);
	//arrows of changing language
	arrow1.setPosition(width / 3 + 430, 577);
	arrow1.setRotation(90);
	arrow1.setFillColor(Color::Black);
	//--------------------------
	arrow2.setPosition(width / 3 + 126, 597);
	arrow2.setRotation(270);
	arrow2.setFillColor(Color::Black);
	scroll_down(choose_option);
	bool blockmove1 = 0, blockmove2 = 0, openess = 0, keyfree = 1, keyplayer = 0, previousbutton1 = 0, previousbutton2 = 0, button_pressed = false, letter_opened = 0,
		endstage = 0, complete = 0, pause1 = 1, pause2 = 1, collp1 = 0, collp2 = 0;
	bool failed1 = false, failed2 = false, ending1 = false, ending2 = false;
	int counter_fail_1 = 3, counter_fail_2 = 3;
	Texture dooro, doorc, key, spike, game_over;
	RectangleShape pass_bg(Vector2f(1920, 1080));
	Text retry, main_menu_text, lose_text, sign_text[3], F_retry, F_main, check, letter_text2[5];
	clear.setFont(font);
	clear.setCharacterSize(80);
	clear.setPosition(3000, 300);
	clear.setString("CLEAR");
	clear.setFillColor(Color::Red);
	main_menu_text.setFont(font);
	main_menu_text.setString("MAIN    MENU");
	main_menu_text.setFillColor(Color::Red);
	main_menu_text.setCharacterSize(40);
	name_player1.setFont(font);
	name_player1.setCharacterSize(20);
	name_player1.setString(name4);
	name_player1.setFillColor(Color(100, 50, 50));
	name_player2.setFont(font);
	name_player2.setCharacterSize(20);
	name_player2.setString(name3);
	name_player2.setFillColor(Color(100, 50, 50));
	spike.loadFromFile("Spike.png");
	dooro.loadFromFile("opened_door.png");
	doorc.loadFromFile("closed_door.png");
	key.loadFromFile("key.png");
	Sign.setTexture(sign);
	Sign.setScale(.2, .2);
	Sign.setPosition(4160, 833 - sign.getSize().y * Sign.getScale().y);
	E_button.setPosition(Sign.getPosition().x + (sign.getSize().x * Sign.getScale().x) / 2.f - e_button.getSize().x / 2.f, 770 - sign.getSize().y * Sign.getScale().y);
	Spike.setTexture(spike);
	Key.setTexture(key);
	Dooro.setTexture(dooro);
	Doorc.setTexture(doorc);
	Spike.setPosition(2650 + 128 * 2, 955 - 66); //  pos1=2650+128*2, 955-66 pos2=2650+128*16-78,955-66
	Key.setScale(0.15f, 0.15f);
	Key.setPosition(200, 300);
	Doorc.setScale(0.3f, 0.3f);
	Dooro.setScale(0.71f, 0.71f);
	Doorc.setPosition(4260, 575);
	Dooro.setPosition(4260, 575);
	//text
	Letter.setTexture(letter);
	Letter.setScale(1.5, 1.3);
	Letter.setPosition(4070, 140);
	for (int i = 0; i < 5; i++) {
		letter_text2[i].setFont(font);
		letter_text2[i].setCharacterSize(20);
		letter_text2[i].setFillColor(Color::Black);
	}
	letter_text2[0].setPosition(4140, 190);
	letter_text2[0].setString("CONGRATULATIONS");
	letter_text2[1].setPosition(4130, 260);
	letter_text2[1].setString("TO   UNLOCK   LEVEL   3");
	letter_text2[2].setPosition(4150, 360);
	letter_text2[2].setString("KEEP   IT   SECRET");
	letter_text2[3].setPosition(4130, 420);
	letter_text2[3].setString("#FREE_PALESTINE");
	letter_text2[4].setPosition(4140, 300);
	letter_text2[4].setString("   PRESS   [F3]   [F5]");
	//Background
	Texture  backgroundTx;
	backgroundTx.loadFromFile("white.png");
	Sprite  background[2];
	for (int i = 0; i < 2; i++)
	{
		background[i].setTexture(backgroundTx);
		background[i].setPosition(Vector2f(i * 1920, 0));
		background[i].setScale(500, 500);
	}
	//View
	View view;
	View cameraView;
	cameraView.setSize(1920, 1080 - 100);
	//Ground
	Texture Ground;
	Ground.loadFromFile("Ground.png");
	Block1.setTexture(Ground);
	Block1.setScale(1, 8);
	Block1.setPosition(1200, 821);
	Block2.setTexture(Ground);
	Block2.setScale(1, 8);
	Block2.setPosition(800, 821);
	heart.loadFromFile("./NinjaAdventure/icons/hearts.png");
	for (int i = 0; i < 3; i++)
	{
		hearts[i].setTexture(heart);
		hearts[i].setScale(.09f, .09f);
		hearts2[i].setTexture(heart);
		hearts2[i].setScale(.09f, .09f);
	}
	//game_over sprite
	game_over.loadFromFile("./NinjaAdventure/icons/game_over.png");
	Game_over.setTexture(game_over);
	name_player1.setFont(font);
	name_player1.setCharacterSize(20);
	name_player1.setString(name3);
	name_player1.setFillColor(Color(100, 50, 50));
	name_player2.setFont(font);
	name_player2.setCharacterSize(20);
	name_player2.setString(name4);
	name_player2.setFillColor(Color(100, 50, 50));
	//properties of pass_bg	
	pass_bg.setFillColor(Color(150, 0, 150));
	retry.setFont(font);
	retry.setString("RETRY");
	retry.setFillColor(Color::Red);
	retry.setCharacterSize(40);
	Sprite g[ng2];
	for (int i = 0; i < ng2; i++)
		g[i].setTexture(Ground);
	g[0].setPosition(0, 950);
	g[0].setScale(10, 7);
	g[1].setPosition(1250, 950);
	g[1].setScale(10, 7);
	g[2].setPosition(-1200, 0);
	g[2].setScale(10, 70);
	g[3].setPosition(4060, 820);
	g[3].setScale(5, 10);
	g[4].setPosition(2650, 620);
	g[4].setScale(1, 18);
	g[5].setPosition(2650, 800);
	g[5].setScale(2, 10);
	g[6].setPosition(2650, 950);
	g[6].setScale(16, 7);
	g[7].setPosition(4680, 0);
	g[7].setScale(10, 90);

	//Sprites
	PLAYERNEEDS_1 player_1;
	PLAYERNEEDS_2 player_2;
	//texture of walking player1	
	//-----------------------------------
	player_1.dead[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	player_1.dead[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_1.dead[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_1.dead[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_1.dead[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_1.dead[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	player_1.dead[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	player_1.dead[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	//------------------------------------
	player_1.faceset[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	player_1.faceset[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_1.faceset[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_1.faceset[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_1.faceset[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_1.faceset[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	player_1.faceset[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	player_1.faceset[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	//------------------------------------
	player_1.walk[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	player_1.walk[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_1.walk[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_1.walk[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_1.walk[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_1.walk[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	player_1.walk[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	player_1.walk[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	//-------------------------------
	player_1.jump[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	player_1.jump[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_1.jump[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_1.jump[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_1.jump[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_1.jump[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	player_1.jump[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	player_1.jump[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	//-----------------------------------
	player_1.idle[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	player_1.idle[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_1.idle[2].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_1.idle[3].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_1.idle[4].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_1.idle[5].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	player_1.idle[6].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	player_1.idle[7].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	//------------------------------------
	player_1.scale = 5;
	player_1.jumpheight = 200.0f;
	//------------------------------------
	for (int i = 0; i < 8; i++)
	{
		player[i].setTexture(player_1.jump[i]);
		player_dead[i].setTexture(player_1.dead[i]);
		faceset[i].setTexture(player_1.faceset[i]);
	}
	faceset[x].setScale(2, 1);
	player_dead[x].setScale(6, 5);
	player[x].setScale(player_1.scale, player_1.scale);
	player[x].setPosition(500, 200);
	player[x].setOrigin(8, 8);
	//-------------------------------------
	player_2.walk[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/Walk.png");
	player_2.walk[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/Walk.png");
	player_2.walk[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/Walk.png");
	player_2.walk[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/Walk.png");
	//-------------------------------------
	player_2.jump[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/jump.png");
	player_2.jump[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/jump.png");
	player_2.jump[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/jump.png");
	player_2.jump[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/jump.png");
	//-------------------------------------
	player_2.idle[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/idle.png");
	player_2.idle[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/idle.png");
	player_2.idle[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/idle.png");
	player_2.idle[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/idle.png");
	//-------------------------------------
	player_2.dead[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/SeparateAnim/dead.png");
	player_2.dead[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/SeparateAnim/dead.png");
	player_2.dead[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/SeparateAnim/dead.png");
	player_2.dead[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/SeparateAnim/dead.png");
	//-------------------------------------
	player_2.faceset[0].loadFromFile("./NinjaAdventure/Actor/Characters/RedNinja/Faceset.png");
	player_2.faceset[1].loadFromFile("./NinjaAdventure/Actor/Characters/RedCamouflage/Faceset.png");
	player_2.faceset[2].loadFromFile("./NinjaAdventure/Actor/Characters/Inspector/Faceset.png");
	player_2.faceset[3].loadFromFile("./NinjaAdventure/Actor/Characters/EggBoy/Faceset.png");
	//-------------------------------------
	player_2.scale = 5;
	player_2.jumpheight = 200.0f;
	//-------------------------------------
	for (int i = 0; i < 4; i++)
	{
		player2[i].setTexture(player_2.jump[i]);
		player2_dead[i].setTexture(player_2.dead[i]);
		faceset2[i].setTexture(player_2.faceset[i]);
	}
	faceset2[x2].setScale(2, 1);
	player2_dead[x2].setScale(6, 5);
	player2[x2].setScale(player_2.scale, player_2.scale);
	player2[x2].setPosition(600, 200);
	player2[x2].setOrigin(8, 8);
	Clock animationclock[6];
	for (int i = 0; i < 6; i++)
	{
		animationclock[i].restart();
	}
	int idlex1 = 0, idlex2 = 0;
	int righty1 = 0, righty2 = 0;
	int lefty1 = 0, lefty2 = 0;
	bool jumped = 0, jumped2 = 0, isAbove1 = 0, isAbove2 = 0;
	int veiwcom = 960, previousbutton3 = 0, previousbutton4 = 0;
	bool rightness = 1;

	while (window.isOpen())
	{
		gameclock2.restart();
		gameclock.restart();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if ((Keyboard::isKeyPressed(Keyboard::Escape) && !previousbutton1) || (back_isselected() && Keyboard::isKeyPressed(Keyboard::Return) && !previousbutton2)) {
				if (!failed1 && !failed2 && !complete) {
					pause_unpause(gamecontrol);
					lang_update_anima();
				}
			}
			if (failed1 || failed2 || complete) {
				if (!gamecontrol)
					pause_unpause(gamecontrol);
			}
			previousbutton1 = Keyboard::isKeyPressed(Keyboard::Escape);
			previousbutton2 = Keyboard::isKeyPressed(Keyboard::Return);

			if (Keyboard::isKeyPressed(Keyboard::D) && !gamecontrol) {
				if (!gamecontrol) {
					if (cnt_music != 4)
						turnup_music(choose_option, cnt_music);
					turnup_sound(choose_option, cnt_volume_wasd);
					lang_right(cnt_language);
					lang_update_anima();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::A) && !gamecontrol) {
				if (!gamecontrol) {
					turndown_sound(choose_option, cnt_volume_wasd);
					turndown_music(choose_option, cnt_music);
					lang_right(cnt_language);
					lang_update_anima();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::W) && !gamecontrol && !previousbutton3) {
				if (!gamecontrol) {
					scroll_up(choose_option);
					lang_update_anima();
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::S) && !gamecontrol && !previousbutton4) {
				scroll_down(choose_option);
				lang_update_anima();

			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && !gamecontrol && main_isselected()) {
				pause_unpause(gamecontrol);
				music.stop();
				cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
				cameraView.setSize(1920, 1080);
				window.setView(cameraView);
				main_menu();
				beginning = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && !gamecontrol && select_isselected()) {
				pause_unpause(gamecontrol);
				music.stop();
				cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
				cameraView.setSize(1920, 1080);
				window.setView(cameraView);
				level_select(type_language, music_Volume, name1, name2);
			}
			previousbutton3 = Keyboard::isKeyPressed(Keyboard::W);
			previousbutton4 = Keyboard::isKeyPressed(Keyboard::S);
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				selector = (selector + 1) % 4;
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				selector--;
				if (selector < 0)
					selector = 3;
			}
			if ((selector == 0 || selector == 1) && Keyboard::isKeyPressed(Keyboard::Enter) && (failed1 || failed2))
			{
				music.stop();
				level2();
			}
			if ((selector == 2 || selector == 3) && Keyboard::isKeyPressed(Keyboard::Enter) && (failed1 || failed2))
			{
				music.stop();
				cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
				cameraView.setSize(window.getSize().x, window.getSize().y);
				window.setView(cameraView);
				beginning = true;
				main();
			}
		}
		if (selector == 0 || selector == 1)
		{
			retry.setFillColor(Color::Red);
			F_retry.setFillColor(Color::Red);
		}
		else
		{
			retry.setFillColor(Color::White);
			F_retry.setFillColor(Color::White);
		}
		if (selector == 2 || selector == 3)
		{
			main_menu_text.setFillColor(Color::Red);
			F_main.setFillColor(Color::Red);
		}
		else
		{
			main_menu_text.setFillColor(Color::White);
			F_main.setFillColor(Color::White);
		}
		for (int i = 0; i < 3; i++)
			hearts[i].setPosition(viewxcalc - 800 + 50 * i, window.getSize().y / 20.0);
		for (int i = 0; i < 3; i++)
			hearts2[i].setPosition(viewxcalc - 800 + 50 * i, window.getSize().y / 10.0);
		if (Spike.getPosition().x <= (2650 + 128 * 11 - 78) && gamecontrol && rightness) {
			Spike.move(24, 0);
			if (Spike.getPosition().x > 2650 + 128 * 11 - 78)
				rightness = 0;
		}
		if (Spike.getPosition().x >= (2650 + 128 * 2) && gamecontrol && !rightness) {
			Spike.move(-24, 0);
			if (Spike.getPosition().x < 2650 + 128 * 2)
				rightness = 1;
		}
		if (Spike.getGlobalBounds().intersects(player[x].getGlobalBounds()) || Spike.getGlobalBounds().intersects(player2[x2].getGlobalBounds())) {
			if (Spike.getGlobalBounds().intersects(player[x].getGlobalBounds()))
			{
				ending1 = false;
				ending2 = false;
				counter_fail_1--;
			}
			fall.play();
			if (Spike.getGlobalBounds().intersects(player2[x2].getGlobalBounds()))
			{
				ending1 = false;
				ending2 = false;
				counter_fail_2--;
			}
			fall.play();
			player[x].setPosition(2700, 500);
			player2[x2].setPosition(2650 + 128, 650);
		}
		name_player1.setPosition(player[x].getPosition().x - name_player1.getGlobalBounds().width / 2, player[x].getPosition().y - 100);
		name_player2.setPosition(player2[x2].getPosition().x - name_player2.getGlobalBounds().width / 2, player2[x2].getPosition().y - 100);
		pass_bg.setPosition(viewxcalc - window.getSize().x / 2.0, 0);
		retry.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0, pass_bg.getSize().y / 2.0 + 80);
		main_menu_text.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 50, pass_bg.getSize().y / 2.0 + 200);
		F_retry.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 100, pass_bg.getSize().y / 2.0 + 80);
		F_main.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 130, pass_bg.getSize().y / 2.0 + 200);
		Game_over.setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 - 180, pass_bg.getSize().y / 2.0 - 250);
		player_dead[x].setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 + 20, pass_bg.getSize().y / 2.0 - 250);
		player2_dead[x2].setPosition(viewxcalc - window.getSize().x / 2.0 + pass_bg.getSize().x / 2.0 + 20, pass_bg.getSize().y / 2.0 - 250);
		for (int i = 0; i < 3; i++)
			hearts[i].setPosition(viewxcalc - 870 + 50 * i, window.getSize().y / 10.0);
		for (int i = 0; i < 3; i++)
			hearts2[i].setPosition(viewxcalc - 870 + 50 * i, window.getSize().y / 20.0);
		faceset[x].setPosition(viewxcalc - window.getSize().x / 2.0, window.getSize().y / 10.0);
		faceset2[x2].setPosition(viewxcalc - window.getSize().x / 2.0, window.getSize().y / 20.0);
		pinkback.setPosition(viewxcalc - veiwcom, 0);
		quads[0].position = Vector2f(viewxcalc - veiwcom, 0);
		quads[1].position = Vector2f(viewxcalc + 1920 - veiwcom, 0);
		quads[2].position = Vector2f(viewxcalc - veiwcom, 1080);
		quads[3].position = Vector2f(viewxcalc + 1920 - veiwcom, 1080);
		option.setPosition(viewxcalc + 1920 / 3.f + 110 - veiwcom, 100);
		edit_sound.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 240);
		edit_music.setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 240);
		language.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 500);
		back.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 620);
		choice_english.setPosition(viewxcalc + 1920 / 3.f + 170 - veiwcom, 560);
		choice_francais.setPosition(viewxcalc + 1920 / 3.f + 160 - veiwcom, 562);
		F_option.setPosition(viewxcalc + 1920 / 3.f + 80 - veiwcom, 110);
		F_sound.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 240);
		F_music.setPosition(viewxcalc + 1920 / 3.f + 240 - veiwcom, 240);
		F_language.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 500);
		F_back.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 620);
		Text_box.setPosition(viewxcalc + 1920 / 3.f + 80 - veiwcom, 190);
		Volume_icon[0].setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 300);
		Volume_icon[1].setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 305);
		Volume_icon[2].setPosition(viewxcalc + 1920 / 3.f + 93 - veiwcom, 305);
		Music_icon[0].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
		Music_icon[1].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
		Music_icon[2].setPosition(viewxcalc + 1920 / 3.f + 300 - veiwcom, 305);
		arrow1.setPosition(viewxcalc + 1920 / 3.f + 430 - veiwcom, 577);
		arrow2.setPosition(viewxcalc + 1920 / 3.f + 126 - veiwcom, 597);
		to_lvlsell.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 360);
		to_main.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 430);
		fto_lvlsell.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 360);
		fto_main.setPosition(viewxcalc + 1920 / 3.f + 100 - veiwcom, 430);
		if (animationclock[0].getElapsedTime().asSeconds() >= 0.08) {
			for (int i = 0; i < 8; i++)
			{
				player[i].setTexture(player_1.idle[i]);
				player[i].setTextureRect(IntRect(0, 0, 16, 16));
				/*player.setTextureRect(IntRect(idlex1 * 16, 0, 16, 16));
				idlex1++;
				idlex1 %= 4;*/
			}
			animationclock[0].restart();
		}
		if (animationclock[3].getElapsedTime().asSeconds() >= 0.08) {
			for (int i = 0; i < 4; i++)
			{
				player2[i].setTexture(player_2.idle[i]);
				player2[i].setTextureRect(IntRect(0, 0, 16, 16));
				/*player2.setTextureRect(IntRect(idlex2 * 16, 0, 16, 16));
				idlex2++;
				idlex2 %= 4;*/
			}
			animationclock[3].restart();
		}
		if (player2[x2].getGlobalBounds().intersects(Block1.getGlobalBounds())) {
			if (Keyboard::isKeyPressed(Keyboard::Key::A) && player2[x2].getPosition().y > Block1.getPosition().y && player2[x2].getPosition().x > Block1.getPosition().x) {
				Block1.move(-7, 0);
				if (player[x].getPosition().x < Block1.getPosition().x && player[x].getGlobalBounds().intersects(Block1.getGlobalBounds()))
				{
					Block1.move(7, 0);
					player2[x2].move(7, 0);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::D) && player2[x2].getPosition().y > Block1.getPosition().y && player2[x2].getPosition().x < Block1.getPosition().x) {
				Block1.move(7, 0);
				if (player[x].getPosition().x > Block1.getPosition().x && player[x].getGlobalBounds().intersects(Block1.getGlobalBounds()))
				{
					Block1.move(-7, 0);
					player2[x2].move(-7, 0);
				}
			}
		}
		if (player[x].getGlobalBounds().intersects(Block1.getGlobalBounds())) {
			if (Keyboard::isKeyPressed(Keyboard::Key::Left) && player[x].getPosition().y > Block1.getPosition().y && player[x].getPosition().x > Block1.getPosition().x)
			{
				Block1.move(-7, 0);
				if (player2[x2].getPosition().x < Block1.getPosition().x && player2[x2].getGlobalBounds().intersects(Block1.getGlobalBounds()))
				{
					Block1.move(7, 0);
					player[x].move(7, 0);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && player[x].getPosition().y > Block1.getPosition().y && player[x].getPosition().x < Block1.getPosition().x)
			{
				Block1.move(7, 0);
				if (player2[x2].getPosition().x > Block1.getPosition().x && player2[x2].getGlobalBounds().intersects(Block1.getGlobalBounds()))
				{
					Block1.move(-7, 0);
					player[x].move(-7, 0);
				}
			}
		}
		if (Block1.getPosition().x > 2402) {
			Block1.setPosition(2402, 821);
			if (Keyboard::isKeyPressed(Keyboard::Key::D)) {

				player2[x2].move(-7, 0);

			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {

				player[x].move(-7, 0);

			}
		}
		if (Block1.getPosition().x < 1200) {
			Block1.setPosition(1200, 821);
			if (Keyboard::isKeyPressed(Keyboard::Key::A)) {

				player2[x2].move(7, 0);

			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {

				player[x].move(7, 0);

			}
		}
		if (player2[x2].getGlobalBounds().intersects(Block2.getGlobalBounds())) {
			if (Keyboard::isKeyPressed(Keyboard::Key::A) && player2[x2].getPosition().y > Block2.getPosition().y && player2[x2].getPosition().x > Block2.getPosition().x) {
				Block2.move(-7, 0);
				if (player[x].getPosition().x < Block2.getPosition().x && player[x].getGlobalBounds().intersects(Block2.getGlobalBounds()))
				{
					Block2.move(7, 0);
					player2[x2].move(7, 0);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::D) && player2[x2].getPosition().y > Block2.getPosition().y && player2[x2].getPosition().x < Block2.getPosition().x) {
				Block2.move(7, 0);
				if (player[x].getPosition().x > Block2.getPosition().x && player[x].getGlobalBounds().intersects(Block2.getGlobalBounds()))
				{
					Block2.move(-7, 0);
					player2[x2].move(-7, 0);
				}
			}
		}
		if (player[x].getGlobalBounds().intersects(Block2.getGlobalBounds())) {
			if (Keyboard::isKeyPressed(Keyboard::Key::Left) && player[x].getPosition().y > Block2.getPosition().y && player[x].getPosition().x > Block2.getPosition().x)
			{
				Block2.move(-7, 0);
				if (player2[x2].getPosition().x < Block2.getPosition().x && player2[x2].getGlobalBounds().intersects(Block2.getGlobalBounds()))
				{
					Block2.move(7, 0);
					player[x].move(7, 0);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && player[x].getPosition().y > Block2.getPosition().y && player[x].getPosition().x < Block2.getPosition().x)
			{
				Block2.move(7, 0);
				if (player2[x2].getPosition().x > Block2.getPosition().x && player2[x2].getGlobalBounds().intersects(Block2.getGlobalBounds()))
				{
					Block2.move(-7, 0);
					player[x].move(-7, 0);
				}
			}
		}
		if (Block2.getPosition().x < 210) {
			Block2.setPosition(210, 821);
			if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
				player2[x2].move(7, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
				player[x].move(7, 0);
			}
		}
		if (Block2.getPosition().x > 900) {
			Block2.setPosition(900, 821);
			if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
				player2[x2].move(-7, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				player[x].move(-7, 0);
			}
		}
		for (int p = 0; p < 8; p++) {
			for (int j = 0; j < 4; j++) {
				if (player2[j].getGlobalBounds().intersects(Key.getGlobalBounds()) && keyfree) {
					keyfree = 0;
					keyplayer = 1;
					col_key.play();
				}
				if (player[p].getGlobalBounds().intersects(Key.getGlobalBounds()) && keyfree) {
					keyfree = 0;
					keyplayer = 0;
					col_key.play();
				}
				if (!keyplayer && !keyfree) {
					Key.setPosition(player[x].getPosition().x - 100, player[x].getPosition().y - 100);
				}
				if (keyplayer && !keyfree) {
					Key.setPosition(player2[x2].getPosition().x - 100, player2[x2].getPosition().y - 100);
				}
				if ((player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && !keyfree && !keyplayer) {
					Key.setScale(0, 0);
					endstage = 1;
				}
				if ((player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && !keyfree && keyplayer) {
					Key.setScale(0, 0);
					endstage = 1;
				}
				if (endstage) {
					openess = 1;
				}
				else {
					openess = 0;
				}
				if ((player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && openess) {
					pause1 = 0;
				}
				if ((player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds())) && openess) {
					pause2 = 0;
				}
				if (player[x].getGlobalBounds().intersects(Doorc.getGlobalBounds()) && openess && (player2[x2].getGlobalBounds().intersects(Doorc.getGlobalBounds()))) {
					complete = 1;
				}
			}
		}
		if (player[x].getGlobalBounds().intersects(Sign.getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(Sign.getGlobalBounds())) {
			if (Keyboard::isKeyPressed(Keyboard::E))
				letter_opened = true;
			else if (player[x].getGlobalBounds().intersects(Sign.getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(Sign.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Escape))
				letter_opened = false;
		}
		if (counter_fail_1 == 0)
		{
			failed1 = true;
		}
		if (counter_fail_2 == 0)
		{
			failed2 = true;
		}
		if (player[x].getPosition().y > 1200 && player[x].getPosition().y < 1210 || player2[x2].getPosition().y > 1200 && player2[x2].getPosition().y < 1210)
		{
			fall.play();
		}
		if (player[x].getPosition().y > 1500)
		{
			ending1 = false;
			ending2 = false;
			if (player2[x2].getPosition().x <= 300)
			{
				player[x].setPosition(player2[x2].getPosition().x + 100, 300);
				counter_fail_1--;
			}
			else
			{
				player[x].setPosition(player[x].getPosition().x - 100, 300);
				counter_fail_1--;
			}
		}
		if (player2[x2].getPosition().y > 1500)
		{
			ending1 = false;
			ending2 = false;
			if (player[x].getPosition().x <= 300)
			{
				player2[x2].setPosition(player[x].getPosition().x + 100, 300);
				counter_fail_2--;
			}
			else
			{
				player2[x2].setPosition(player[x].getPosition().x - 100, 300);
				counter_fail_2--;
			}
		}

		//WHEN UNCOMMENTED, PLAYER REVOLVES AROUND HIMSELF
		//PLAYER MOVEMENT
		//----------------------------------------------------------------------------------------------------------
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !ending1 && gamecontrol)
		{
			for (int i = 0; i < 8; i++)
			{
				player[i].setScale(player_1.scale, player_1.scale);
				player[i].move(7, 0);
				player[i].setTexture(player_1.walk[i]);
				player[i].setTextureRect(IntRect(3 * 16, righty1 * 16, 16, 16));
			}
			if (animationclock[1].getElapsedTime().asSeconds() >= 0.08) {
				righty1++;
				righty1 %= 4;
				animationclock[1].restart();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D) && !ending2 && gamecontrol)
		{
			for (int i = 0; i < 4; i++)
			{
				player2[i].setScale(player_2.scale, player_2.scale);
				player2[i].move(7, 0);
				player2[i].setTexture(player_2.walk[i]);
				player2[i].setTextureRect(IntRect(3 * 16, righty2 * 16, 16, 16));
			}
			if (animationclock[4].getElapsedTime().asSeconds() >= 0.08) {
				righty2++;
				righty2 %= 4;
				animationclock[4].restart();
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !ending1 && gamecontrol)
		{
			for (int i = 0; i < 8; i++)
			{
				player[i].setScale(player_1.scale, player_1.scale);
				player[i].move(-7, 0);
				player[i].setTexture(player_1.walk[i]);
				player[i].setTextureRect(IntRect(2 * 16, lefty1 * 16, 16, 16));
			}
			if (animationclock[1].getElapsedTime().asSeconds() >= 0.08) {

				lefty1++;
				lefty1 %= 4;
				animationclock[1].restart();
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A) && !ending2 && gamecontrol)
		{
			for (int i = 0; i < 4; i++)
			{
				player2[i].setScale(player_2.scale, player_2.scale);
				player2[i].move(-7, 0);
				player2[i].setTexture(player_2.walk[i]);
				player2[i].setTextureRect(IntRect(2 * 16, lefty2 * 16, 16, 16));
			}
			if (animationclock[4].getElapsedTime().asSeconds() >= 0.08) {
				lefty2++;
				lefty2 %= 4;
				animationclock[4].restart();
			}
		}
		//collision with X
		for (int i = 0; i < ng2; i++)
		{
			if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()) && player[x].getPosition().x < g[i].getPosition().x && g[i].getPosition().y < player[x].getPosition().y)
			{
				for (int y = 0; y < 7; y++)
				{
					if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
						player[x].move(-1, 0);
				}
				player[x].move(-15, 0);
			}
			else if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()) && player[x].getPosition().x > g[i].getPosition().x /*+ Ground.getSize().x*g[i].getScale().x*/ && g[i].getPosition().y < player[x].getPosition().y)
			{
				for (int y = 0; y < 7; y++)
				{
					if (player[x].getGlobalBounds().intersects(g[i].getGlobalBounds()))
						player[x].move(1, 0);
				}
				player[x].move(15, 0);
			}
			if (player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()) && player2[x2].getPosition().x < g[i].getPosition().x && g[i].getPosition().y < player2[x2].getPosition().y)
			{
				for (int y = 0; y < 7; y++)
				{
					if (player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()))
						player2[x2].move(-1, 0);
				}
				player2[x2].move(-15, 0);
			}
			else if (player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()) && player2[x2].getPosition().x > g[i].getPosition().x && g[i].getPosition().y < player2[x2].getPosition().y)
			{
				for (int y = 0; y < 7; y++)
				{
					if (player2[x2].getGlobalBounds().intersects(g[i].getGlobalBounds()))
						player2[x2].move(1, 0);
				}
				player2[x2].move(15, 0);
			}

		}
		//JUMP AND GRAVITY
		//==================================================================================================================
		//Player 1
		//-------------------
		if ((!isGrounded_level2(player, g, Block1, Block2)) && !jumped && !isAbove1)
		{

			player[x].setTexture(player_1.jump[x]); //fall
			player[x].setTextureRect(IntRect(0, 0, 16, 16));
			//player.move(0, animationclk3.getElapsedTime().asSeconds()); WHEN UNCOMMENTED, PLAYER MOVES UP AND DOWN WHEN ON TOP OF THE OTHER PLAYER INSTEAD OF STAYING STILL
			player[x].move(0, 7);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !jumped && gamecontrol && !ending1)
			{
				if (!(failed1 || failed2))
					jump.play();
				jumped = 1;
				player_1.startposition = player[x].getPosition().y;
				animationclock[2].restart();
			}
		}
		if (jumped)
		{
			player[x].setTexture(player_1.jump[x]);
			if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			{
				player[x].setTextureRect(IntRect(2 * 16, 0, 16, 16));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			{

				player[x].setTextureRect(IntRect(3 * 16, 0, 16, 16));
			}
			else
			{
				player[x].setTextureRect(IntRect(0 * 16, 0, 16, 16));
			}
			player[x].move(0, -7);

			if (player_1.startposition - player[x].getPosition().y >= player_1.jumpheight) {
				jumped = 0;
				animationclock[2].restart();
			}
		}
		//Player 2
		//-------------------
		if ((!isGrounded2_level2(player2, g, Block1, Block2)) && !jumped2 && !isAbove2) //to fall down at first
		{
			player2[x2].setTexture(player_2.jump[x2]);
			player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
			//player2.move(0, animation2clk3.getElapsedTime().asSeconds() * 7); //WHEN UNCOMMENTED, PLAYER MOVES UP AND DOWN WHEN ON TOP OF THE OTHER PLAYER INSTEAD OF STAYING STILL
			player2[x2].move(0, 7);
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::W) && !jumped2 && gamecontrol && !ending2)
			{
				if (!(failed1 || failed2))
					jump.play();
				jumped2 = 1;
				player_2.startposition = player2[x2].getPosition().y;
				animationclock[5].restart();
			}
		}
		if (jumped2)
		{

			player2[x2].setTexture(player_2.jump[x2]);
			if (Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				player2[x2].setTextureRect(IntRect(2 * 16, 0, 16, 16));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				player2[x2].setTextureRect(IntRect(3 * 16, 0, 16, 16));
			}
			else
			{
				player2[x2].setTextureRect(IntRect(0 * 16, 0, 16, 16));
			}

			player2[x2].move(0, -7);
			if (player_2.startposition - player2[x2].getPosition().y >= player_2.jumpheight)
			{
				jumped2 = 0;
				animationclock[5].restart();
			}

		}
		//PLAYER COLLISON 
		//----------------------------------------------------------------------------------------------------------------------

		if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && ((player[x].getPosition().y > player2[x2].getPosition().y) || (player[x].getPosition().y < player2[x2].getPosition().y)))
		{
			if (player[x].getPosition().y < player2[x2].getPosition().y) {

				player[x].setTexture(player_1.idle[x]);
				player[x].setTextureRect(IntRect(0, 0, 16, 16));
				player[x].move(0, -7);
				isAbove1 = 1;
			}
			else if (player[x].getPosition().y > player2[x].getPosition().y) {

				player2[x2].setTexture(player_2.idle[x2]);
				player2[x2].setTextureRect(IntRect(0, 0, 16, 16));
				player2[x2].move(0, -7);
				isAbove2 = 1;
			}
		}
		else
		{
			isAbove1 = 0; isAbove2 = 0;
			if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Left))
			{
				player[x].move(7, 0);

			}
			if (player[x].getGlobalBounds().intersects(player2[x2].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				player[x].move(-7, 0);
			}

			if (player2[x2].getGlobalBounds().intersects(player[x].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				player2[x2].move(7, 0);

			}

			if (player2[x2].getGlobalBounds().intersects(player[x].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				player2[x2].move(-7, 0);
			}
		}
		if (!ending1)
		{
			window.draw(player[x]);
			player[x].setScale(5, 5);
		}
		else
			player[x].setScale(.1, .1);
		if (!ending2)
		{
			window.draw(player2[x2]);
			player2[x2].setScale(5, 5);
		}
		else
			player2[x2].setScale(.1, .1);
		viewdeltax = abs(player[x].getPosition().x - player2[x2].getPosition().x);
		if (viewdeltax >= (window.getSize().x - player_1.idle[x].getSize().x)) {//player1 arrows ; player2 wasd
			extreme_x = 1; //can be used to pause calculation of viewxcalc for optimisation
		}
		else {
			extreme_x = 0;
		}
		if (extreme_x)
		{
			if (player[x].getPosition().x > player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::A))
					player2[x2].move(7, 0);//or player2.move(-7,0);
				player[x].move(-7, 0);//or player1.move(7,0);
			}
			else if (player[x].getPosition().x > player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::Right))
					player[x].move(-7, 0);//or player2.move(-7,0);
				player2[x2].move(7, 0);//or player2.move(-7,0);
			}
			if (player[x].getPosition().x < player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::Left))
					player[x].move(7, 0);//or player1.move(-7,0);
				player2[x2].move(-7, 0);//or player2.move(7,0);
			}
			else if (player[x].getPosition().x < player2[x2].getPosition().x && Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::A))
					player2[x2].move(-7, 0);//or player1.move(-7,0);
				player[x].move(7, 0);//or player2.move(-7,0);
			}
		}
		if (timer < 3)
		{
			cameraView.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.0);
			window.setView(cameraView);
			is_int = 1;
		}
		else {
			viewxcalc = (player[x].getPosition().x + player2[x2].getPosition().x) / 2.f;//before window.clear
			if (viewxcalc > 3800)
				viewxcalc = 3800;
			cameraView.setCenter(viewxcalc, window.getSize().y - 500);
			if (viewxcalc < 1000)
				viewxcalc = 1000;
			cameraView.setCenter(viewxcalc, window.getSize().y - 500);
			is_int = 0;
		}
		if (!ending1 && player[x].getGlobalBounds().intersects(Dooro.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::RShift) && openess)
			ending1 = true;
		else if (ending1 && Keyboard::isKeyPressed(Keyboard::Key::RShift) && !ending2)
			ending1 = false;
		if (!ending2 && player2[x2].getGlobalBounds().intersects(Dooro.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::LShift) && openess)
			ending2 = true;
		else if (ending2 && Keyboard::isKeyPressed(Keyboard::Key::LShift) && !ending1)
			ending2 = false;
		window.clear();
		window.setView(cameraView);
		if (!pause1)
			window.draw(player[x]);
		if (!pause2)
			window.draw(player2[x2]);
		for (int i = 0; i < 2; i++)
			window.draw(background[i]);
		window.draw(Sign);
		//Draw Map
		for (int i = 0; i < ng2; i++)
			window.draw(g[i]);
		window.draw(Block1);
		window.draw(Block2);
		if (openess) {
			window.draw(Dooro);
		}
		else
			window.draw(Doorc);
		if (!ending1)
		{
			window.draw(player[x]);
			player[x].setScale(5, 5);
		}
		else
		{
			player[x].setScale(0, 0);
			if (!isGrounded_level2(player, g, Block1, Block2))
				player[x].move(0, -7);
		}
		if (!ending2)
		{
			window.draw(player2[x2]);
			player2[x2].setScale(5, 5);
		}
		else
		{
			player2[x2].setScale(0, 0);
			if (!isGrounded2_level2(player2, g, Block1, Block2))
				player2[x2].move(0, -7);
		}
		if (timer2 > 5)
		{
			Pass3 = true;
			level3();
		}
		if (!is_int)
		{
			for (int i = 0; i < counter_fail_1; i++)
				window.draw(hearts[i]);
			for (int i = 0; i < counter_fail_2; i++)
				window.draw(hearts2[i]);
			window.draw(faceset[x]);
			window.draw(faceset2[x2]);
		}
		embeddeddraw_intro_lvl2();
		if (letter_opened)
		{
			window.draw(Letter);
			for (int i = 0; i < 5; i++)
				window.draw(letter_text2[i]);
		}
		window.draw(Key);
		window.draw(Spike);
		window.draw(E_button);
		if (ending1 && ending2)
		{
			music.stop();
			window.draw(clear);
			if (clear.getPosition().x <= (3800 - clear.getGlobalBounds().width / 2.f))
				clear.move(20, 0);
			else
				next = 1;
		}
		if ((player[x].getGlobalBounds().intersects(Dooro.getGlobalBounds()) || player2[x2].getGlobalBounds().intersects(Dooro.getGlobalBounds())) && !ending1 && !ending2)
			window.draw(Shift);
		if (cnt_music == 0)
			music.stop();
		else if (cnt_music == 1)
		{
			cnt_music = 4;
			music.play();
			music.setVolume(music_Volume * cnt_music);
		}
		jump.setVolume(sound_volume * cnt_volume_wasd);
		fall.setVolume(sound_volume * cnt_volume_wasd);
		col_key.setVolume(sound_volume * cnt_volume_wasd);
		embedded_draw_pause();
		if (!ending1)
			window.draw(name_player1);
		if (!ending2)
			window.draw(name_player2);
		if (failed1 || failed2)
		{
			music.stop();
			window.draw(pass_bg);
			if (!type_language)
			{
				window.draw(retry);
				window.draw(main_menu_text);
			}
			else
			{
				window.draw(F_retry);
				window.draw(F_main);
			}
			window.draw(Game_over);
			if (counter_fail_1 == 0)
				window.draw(player_dead[x]);
			if (counter_fail_2 == 0)
				window.draw(player2_dead[x2]);
		}
		window.display();
		timer += gameclock.getElapsedTime().asSeconds();
		if (next)
			timer2 += gameclock2.getElapsedTime().asSeconds();
	}
}
void  lvl1_intro(float wid, float hei) {
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	lvl1.levelselected = "level 1";
	lvl1.startshape.loadFromFile("./NinjaAdventure/HUD/Dialog/ChoiceBox.png");
	lvl1.temp.setTexture(lvl1.startshape);
	lvl1.temp.setScale(10.f, 10.f);
	lvl1.temp.setPosition((wid - (lvl1.startshape.getSize().x * lvl1.temp.getScale().x)) / 2.f
		, (hei - (lvl1.startshape.getSize().y * lvl1.temp.getScale().y)) / 2.f);
	lvl1.starttext.setFont(font);
	lvl1.starttext.setCharacterSize(36);
	lvl1.starttext.setString(lvl1.levelselected);
	lvl1.starttext.setFillColor(Color(100, 30, 30));
	lvl1.starttext.setPosition((wid - lvl1.starttext.getLocalBounds().width) / 2.f,
		((hei - lvl1.starttext.getLocalBounds().height) / 2.f) - lvl1.starttext.getLocalBounds().top);

}
void  lvl2_intro(float wid, float hei) {

	lvl2.levelselected = "level 2";
	lvl2.startshape.loadFromFile("./NinjaAdventure/HUD/Dialog/ChoiceBox.png");
	lvl2.temp.setTexture(lvl2.startshape);
	lvl2.temp.setScale(10.f, 10.f);
	lvl2.temp.setPosition((wid - (lvl2.startshape.getSize().x * lvl2.temp.getScale().x)) / 2.f
		, (hei - (lvl2.startshape.getSize().y * lvl2.temp.getScale().y)) / 2.f);

	lvl2.starttext.setFont(font);
	lvl2.starttext.setCharacterSize(36);
	lvl2.starttext.setString(lvl2.levelselected);
	lvl2.starttext.setFillColor(Color(100, 30, 30));
	lvl2.starttext.setPosition(((wid - lvl2.starttext.getGlobalBounds().width) / 2.f) - 50,
		(((hei - lvl2.starttext.getGlobalBounds().height) / 2.f) - lvl2.starttext.getGlobalBounds().top) + 10);

}
void  lvl3_intro(float wid, float hei) {
	font.loadFromFile("./NinjaAdventure/HUD/Font/NormalFont.ttf");
	lvl3.levelselected = "level 3";
	lvl3.startshape.loadFromFile("./NinjaAdventure/HUD/Dialog/ChoiceBox.png");
	lvl3.temp.setTexture(lvl3.startshape);
	lvl3.temp.setScale(10.f, 10.f);
	lvl3.temp.setPosition((wid - (lvl3.startshape.getSize().x * lvl3.temp.getScale().x)) / 2.f
		, (hei - (lvl3.startshape.getSize().y * lvl3.temp.getScale().y)) / 2.f);

	lvl3.starttext.setFont(font);
	lvl3.starttext.setCharacterSize(36);
	lvl3.starttext.setString(lvl3.levelselected);
	lvl3.starttext.setFillColor(Color(100, 30, 30));
	lvl3.starttext.setPosition((wid - lvl3.starttext.getLocalBounds().width) / 2.f,
		((hei - lvl3.starttext.getLocalBounds().height) / 2.f) - lvl3.starttext.getLocalBounds().top);

}
void  embeddeddraw_intro_lvl1()
{
	if (timer < 3)
	{
		window.draw(lvl1.temp);
		window.draw(lvl1.starttext);
	}
}
void  embeddeddraw_intro_lvl2()
{
	if (timer < 3)
	{
		window.draw(lvl2.temp);
		window.draw(lvl2.starttext);
	}
}
void  embeddeddraw_intro_lvl3()
{
	if (timer < 3)
	{
		window.draw(lvl3.temp);
		window.draw(lvl3.starttext);
	}
}
void  scroll_down(int& choose) {
	choose++;
	choose %= 6;
	if (choose_option == 0)
	{
		edit_sound.setFillColor(Color::Red);
		F_sound.setFillColor(Color::Red);
		edit_sound.setOutlineThickness(0);
		F_sound.setOutlineThickness(0);
	}
	else
	{
		edit_sound.setFillColor(Color::White);
		F_sound.setFillColor(Color::White);
		edit_sound.setOutlineThickness(1);
		F_sound.setOutlineThickness(1);
	}

	if (choose_option == 1)
	{
		edit_music.setFillColor(Color::Red);
		edit_music.setOutlineThickness(0);
		F_music.setFillColor(Color::Red);
		F_music.setOutlineThickness(0);
	}
	else
	{
		edit_music.setFillColor(Color::White);
		edit_music.setOutlineThickness(1);
		F_music.setFillColor(Color::White);
		F_music.setOutlineThickness(1);
	}
	if (choose_option == 2)
	{
		to_lvlsell.setFillColor(Color::Red);
		to_lvlsell.setOutlineThickness(0);
		fto_lvlsell.setFillColor(Color::Red);
		fto_lvlsell.setOutlineThickness(0);
	}
	else
	{
		to_lvlsell.setFillColor(Color::White);
		to_lvlsell.setOutlineThickness(1);
		fto_lvlsell.setFillColor(Color::White);
		fto_lvlsell.setOutlineThickness(1);
	}
	if (choose_option == 3)
	{
		to_main.setFillColor(Color::Red);
		to_main.setOutlineThickness(0);
		fto_main.setFillColor(Color::Red);
		fto_main.setOutlineThickness(0);
	}
	else
	{
		to_main.setFillColor(Color::White);
		to_main.setOutlineThickness(1);
		fto_main.setFillColor(Color::White);
		fto_main.setOutlineThickness(1);
	}
	if (choose_option == 4)
	{
		language.setFillColor(Color::Red);
		language.setOutlineThickness(0);
		F_language.setFillColor(Color::Red);
		F_language.setOutlineThickness(0);
	}
	else
	{
		language.setFillColor(Color::White);
		language.setOutlineThickness(1);
		F_language.setFillColor(Color::White);
		F_language.setOutlineThickness(1);
	}
	if (choose_option == 5)
	{
		back.setFillColor(Color::Red);
		back.setOutlineThickness(0);
		F_back.setFillColor(Color::Red);
		F_back.setOutlineThickness(0);
	}
	else
	{
		back.setFillColor(Color::White);
		back.setOutlineThickness(1);
		F_back.setFillColor(Color::White);
		F_back.setOutlineThickness(1);
	}

}
void  scroll_up(int& choose) {
	choose--;
	if (choose < 0) {
		choose = 5;
	}
	if (choose_option == 0)
	{
		edit_sound.setFillColor(Color::Red);
		F_sound.setFillColor(Color::Red);
		edit_sound.setOutlineThickness(0);
		F_sound.setOutlineThickness(0);
	}
	else
	{
		edit_sound.setFillColor(Color::White);
		F_sound.setFillColor(Color::White);
		edit_sound.setOutlineThickness(1);
		F_sound.setOutlineThickness(1);
	}

	if (choose_option == 1)
	{
		edit_music.setFillColor(Color::Red);
		edit_music.setOutlineThickness(0);
		F_music.setFillColor(Color::Red);
		F_music.setOutlineThickness(0);
	}
	else
	{
		edit_music.setFillColor(Color::White);
		edit_music.setOutlineThickness(1);
		F_music.setFillColor(Color::White);
		F_music.setOutlineThickness(1);
	}
	if (choose_option == 2)
	{
		to_lvlsell.setFillColor(Color::Red);
		to_lvlsell.setOutlineThickness(0);
		fto_lvlsell.setFillColor(Color::Red);
		fto_lvlsell.setOutlineThickness(0);
	}
	else
	{
		to_lvlsell.setFillColor(Color::White);
		to_lvlsell.setOutlineThickness(1);
		fto_lvlsell.setFillColor(Color::White);
		fto_lvlsell.setOutlineThickness(1);
	}
	if (choose_option == 3)
	{
		to_main.setFillColor(Color::Red);
		to_main.setOutlineThickness(0);
		fto_main.setFillColor(Color::Red);
		fto_main.setOutlineThickness(0);
	}
	else
	{
		to_main.setFillColor(Color::White);
		to_main.setOutlineThickness(1);
		fto_main.setFillColor(Color::White);
		fto_main.setOutlineThickness(1);
	}
	if (choose_option == 4)
	{
		language.setFillColor(Color::Red);
		language.setOutlineThickness(0);
		F_language.setFillColor(Color::Red);
		F_language.setOutlineThickness(0);
	}
	else
	{
		language.setFillColor(Color::White);
		language.setOutlineThickness(1);
		F_language.setFillColor(Color::White);
		F_language.setOutlineThickness(1);
	}
	if (choose_option == 5)
	{
		back.setFillColor(Color::Red);
		back.setOutlineThickness(0);
		F_back.setFillColor(Color::Red);
		F_back.setOutlineThickness(0);
	}
	else
	{
		back.setFillColor(Color::White);
		back.setOutlineThickness(1);
		F_back.setFillColor(Color::White);
		F_back.setOutlineThickness(1);
	}

}
void  lang_left(int& cnt_language) {
	if (choose_option == 4 || choose_option == 3) {
		cnt_language += 1;
		cnt_language %= 4;
	}

}
void  lang_right(int& cnt_language) {
	if (choose_option == 4 || choose_option == 3) {
		cnt_language--;
		if (cnt_language < 0)
			cnt_language = 2;
	}
}
void  lang_update_anima() {
	if ((cnt_language == 0 || cnt_language == 1) && (choose_option == 4))
	{
		choice_english.setFillColor(Color::Red);
	}
	else
	{
		choice_english.setFillColor(Color(0, 150, 600));
	}
	if ((cnt_language == 2 || cnt_language == 3) && (choose_option == 4))
	{
		choice_francais.setFillColor(Color::Red);
	}
	else
	{
		choice_francais.setFillColor(Color(0, 150, 600));
	}
}
int   back_isselected() {
	bool returne = 0;
	if (choose_option == 5) {
		returne = 1;
	}
	else {
		returne = 0;
	}
	if (gamecontrol) {
		returne = 0;
	}
	return returne;
}
int   select_isselected() {
	bool returne = 0;
	if (choose_option == 2) {
		returne = 1;
	}
	else {
		returne = 0;
	}
	if (gamecontrol) {
		returne = 0;
	}
	return returne;
}
int   main_isselected() {
	bool returne = 0;
	if (choose_option == 3) {
		returne = 1;
	}
	else {
		returne = 0;
	}
	if (gamecontrol) {
		returne = 0;
	}
	return returne;
}
void  pause_unpause(bool& gamecontrol) {
	gamecontrol = !gamecontrol;
}
void  embedded_draw_pause() {
	//draw
	if (!gamecontrol) {
		window.draw(pinkback);
		window.draw(quads);
		window.draw(Text_box);
		//english
		if (cnt_language == 0 || cnt_language == 1)
		{
			window.draw(option);
			window.draw(edit_sound);
			window.draw(edit_music);
			window.draw(language);
			window.draw(back);
			window.draw(to_lvlsell);
			window.draw(to_main);
		}
		//french
		if (cnt_language == 2 || cnt_language == 3)
		{
			window.draw(F_option);
			window.draw(F_sound);
			window.draw(F_music);
			window.draw(F_language);
			window.draw(F_back);
			window.draw(fto_lvlsell);
			window.draw(fto_main);
		}
		//changing language
		if (cnt_language == 0 || cnt_language == 1)
			window.draw(choice_english);
		if (cnt_language == 2 || cnt_language == 3)
			window.draw(choice_francais);
		//changing between sound icons
		if (cnt_volume_wasd == 0)
			window.draw(Volume_icon[2]);
		else if (cnt_volume_wasd == 4)
			window.draw(Volume_icon[0]);
		else
			window.draw(Volume_icon[0]);
		//changing between music icons
		if (cnt_music == 0)
			window.draw(Music_icon[2]);
		else if (cnt_music == 4)
			window.draw(Music_icon[0]);
		else
			window.draw(Music_icon[0]);
		//show the arrows when selecting language
		if (choose_option == 4)
		{
			window.draw(arrow1);
			window.draw(arrow2);
		}
	}
}
void  turnup_sound(int& choose_option, int& cnt_volume_wasd) {
	if (choose_option == 0) {
		cnt_volume_wasd = 1;
		edit_sound.setFillColor(Color::Red);
		F_sound.setFillColor(Color::Red);
		edit_sound.setOutlineThickness(0);
		F_sound.setOutlineThickness(0);
	}
	else
	{
		edit_sound.setFillColor(Color::White);
		F_sound.setFillColor(Color::White);
		edit_sound.setOutlineThickness(1);
		F_sound.setOutlineThickness(1);
	}
}
void  turnup_music(int& choose_option, int& cnt_music) {
	if (choose_option == 1) {
		cnt_music = 1;
	}
	if (choose_option == 1)
	{
		edit_music.setFillColor(Color::Red);
		edit_music.setOutlineThickness(0);
		F_music.setFillColor(Color::Red);
		F_music.setOutlineThickness(0);
	}
	else
	{
		edit_music.setFillColor(Color::White);
		edit_music.setOutlineThickness(1);
		F_music.setFillColor(Color::White);
		F_music.setOutlineThickness(1);
	}
}
void  turndown_sound(int& choose_option, int& cnt_volume_wasd) {
	if (choose_option == 0) {
		cnt_volume_wasd = 0;
		edit_sound.setFillColor(Color::Red);
		F_sound.setFillColor(Color::Red);
		edit_sound.setOutlineThickness(0);
		F_sound.setOutlineThickness(0);
	}
	else
	{
		edit_sound.setFillColor(Color::White);
		F_sound.setFillColor(Color::White);
		edit_sound.setOutlineThickness(1);
		F_sound.setOutlineThickness(1);
	}
}
void  turndown_music(int& choose_option, int& cnt_music) {
	if (choose_option == 1) {
		cnt_music = 0;
	}
	if (choose_option == 1)
	{
		edit_music.setFillColor(Color::Red);
		edit_music.setOutlineThickness(0);
		F_music.setFillColor(Color::Red);
		F_music.setOutlineThickness(0);
	}
	else
	{
		edit_music.setFillColor(Color::White);
		edit_music.setOutlineThickness(1);
		F_music.setFillColor(Color::White);
		F_music.setOutlineThickness(1);
	}
}
void music_handle() {
	if (beginning == 1) {
		music.openFromFile("./NinjaAdventure/Musics/22 - Dream.ogg");
		music.setLoop(true);
		music.play();
	}
	music.setVolume(music_Volume);
	music.play();
	while (true)
	{
		if (music.getStatus() == music.Playing)
		{
			music.setPlayingOffset(seek_time);
			break;
		}
	}
}
void credit()
{
	credit_fun crd;
	Clock clock;
	window.setFramerateLimit(60);
	//music
	font.loadFromFile("./NinjaAdventure/HUD/Font/KnightWarrior-w16n8.otf");
	crd.music.openFromFile("./NinjaAdventure/Musics/8 - End Theme.ogg");
	crd.music.setLoop(true);
	crd.music.play();
	//background
	crd.background.loadFromFile("./NinjaAdventure/Backgrounds/Tilesets/TilesetField.png");
	crd.Background.setTextureRect(IntRect(0, 60 * 2.5, 60, 60));
	crd.Background.setTexture(crd.background);
	crd.Background.setPosition(-300, -500);
	crd.Background.setScale(50, 50);
	//propeties of banner
	crd.banner.loadFromFile("./NinjaAdventure/icons/OIP__2_-removebg-preview.png");
	crd.Banner.setTexture(crd.banner);
	crd.Banner.setPosition(1370, 100);
	crd.Banner.setScale(1, 3);
	crd.Banner.setRotation(90);
	//properties of textbox
	crd.textbox.loadFromFile("./NinjaAdventure/HUD/Dialog/DialogueBoxSimple.png");
	crd.Textbox.setTexture(crd.textbox);
	crd.Textbox.setPosition(170, 350);
	crd.Textbox.setScale(5, 12);
	//texts
	crd.credit_texts[0].setFont(font);
	crd.credit_texts[0].setString("UI   &  INTEGR");
	crd.credit_texts[0].setFillColor(Color::Black);
	crd.credit_texts[0].setPosition(750, 170);
	crd.credit_texts[0].setCharacterSize(80);
	//------------------------
	crd.credit_texts[1].setFont(font);
	crd.credit_texts[1].setString("LOJAINA   AYMAN");
	crd.credit_texts[1].setFillColor(Color::Black);
	crd.credit_texts[1].setPosition(300, 600);
	crd.credit_texts[1].setCharacterSize(80);
	//-------------------------
	crd.credit_texts[2].setFont(font);
	crd.credit_texts[2].setString("YOUSSEF   WALEED");
	crd.credit_texts[2].setFillColor(Color::Black);
	crd.credit_texts[2].setPosition(1100, 600);
	crd.credit_texts[2].setCharacterSize(80);
	//-------------------------
	crd.credit_texts[3].setFont(font);
	crd.credit_texts[3].setString("AHMED   ALI   MAHDY");
	crd.credit_texts[3].setFillColor(Color::Black);
	crd.credit_texts[3].setPosition(650, 800);
	crd.credit_texts[3].setCharacterSize(80);
	//--------------------------
	crd.credit_texts[4].setFont(font);
	crd.credit_texts[4].setString("MAP");
	crd.credit_texts[4].setFillColor(Color::Black);
	crd.credit_texts[4].setPosition(860, 170);
	crd.credit_texts[4].setCharacterSize(80);
	//-------------------------
	crd.credit_texts[5].setFont(font);
	crd.credit_texts[5].setString("MOHAMMED  EZAT");
	crd.credit_texts[5].setFillColor(Color::Black);
	crd.credit_texts[5].setPosition(300, 670);
	crd.credit_texts[5].setCharacterSize(80);
	//-------------------------
	crd.credit_texts[6].setFont(font);
	crd.credit_texts[6].setString("YOUSSEF   HANY");
	crd.credit_texts[6].setFillColor(Color::Black);
	crd.credit_texts[6].setPosition(1150, 670);
	crd.credit_texts[6].setCharacterSize(80);
	crd.credit_texts[6].setFont(font);
	//-------------------------
	crd.credit_texts[7].setFont(font);
	crd.credit_texts[7].setString("MOVEMENT");
	crd.credit_texts[7].setFillColor(Color::Black);
	crd.credit_texts[7].setPosition(800, 170);
	crd.credit_texts[7].setCharacterSize(80);
	//-------------------------
	crd.credit_texts[8].setFont(font);
	crd.credit_texts[8].setString("JURY   AHMED");
	crd.credit_texts[8].setFillColor(Color::Black);
	crd.credit_texts[8].setPosition(300, 670);
	crd.credit_texts[8].setCharacterSize(80);
	//-------------------------
	crd.credit_texts[9].setFont(font);
	crd.credit_texts[9].setString("YOUSSEF   ATEF");
	crd.credit_texts[9].setFillColor(Color::Black);
	crd.credit_texts[9].setPosition(1180, 670);
	crd.credit_texts[9].setCharacterSize(80);
	//-------------------------
	crd.credit_texts[10].setFont(font);
	crd.credit_texts[10].setString("THANKS   FOR");
	crd.credit_texts[10].setFillColor(Color::Black);
	crd.credit_texts[10].setPosition(780, 170);
	crd.credit_texts[10].setCharacterSize(80);
	//-------------------------
	crd.credit_texts[11].setFont(font);
	crd.credit_texts[11].setString("Patreon: https://www.patreon.com/pixelarchipel");
	crd.credit_texts[11].setFillColor(Color::Black);
	crd.credit_texts[11].setPosition(250, 500);
	crd.credit_texts[11].setCharacterSize(50);
	//-------------------------
	crd.credit_texts[12].setFont(font);
	crd.credit_texts[12].setString("Itchio Page: https://pixel-boy.itch.io/");
	crd.credit_texts[12].setFillColor(Color::Black);
	crd.credit_texts[12].setPosition(250, 700);
	crd.credit_texts[12].setCharacterSize(50);
	//--------------------------
	crd.credit_texts[13].setFont(font);
	crd.credit_texts[13].setString("Pack Page: https://pixel-boy.itch.io/ninja-adventure-asset-pack");
	crd.credit_texts[13].setFillColor(Color::Black);
	crd.credit_texts[13].setPosition(250, 900);
	crd.credit_texts[13].setCharacterSize(50);

	//-------------------------
	crd.credit_texts[14].setFont(font);
	crd.credit_texts[14].setString("PRESS   ANY   KEY  TO   SKIP");
	crd.credit_texts[14].setFillColor(Color::Black);
	crd.credit_texts[14].setPosition(60, 0);
	crd.credit_texts[14].setCharacterSize(40);
	while (window.isOpen())
	{
		clock.restart();
		while (window.pollEvent(e))
		{
			if (e.type == Event::KeyPressed && crd.timer3 > 1)
			{
				crd.music.stop();
				beginning = true;
				main();
			}
			if (e.type == Event::Closed)
			{

				window.close();
			}
		}
		window.clear();
		window.draw(crd.Background);
		window.draw(crd.Banner);
		window.draw(crd.Textbox);
		if (crd.timer3 < 6)
		{
			window.draw(crd.credit_texts[0]);
			window.draw(crd.credit_texts[1]);
			window.draw(crd.credit_texts[2]);
			window.draw(crd.credit_texts[3]);
		}
		else if (crd.timer3 < 12)
		{
			window.draw(crd.credit_texts[4]);
			window.draw(crd.credit_texts[5]);
			window.draw(crd.credit_texts[6]);
		}
		else if (crd.timer3 < 18)
		{
			window.draw(crd.credit_texts[7]);
			window.draw(crd.credit_texts[8]);
			window.draw(crd.credit_texts[9]);
		}
		else if (crd.timer3 < 24)
		{
			window.draw(crd.credit_texts[10]);
			window.draw(crd.credit_texts[11]);
			window.draw(crd.credit_texts[12]);
			window.draw(crd.credit_texts[13]);
		}
		else
		{
			crd.music.stop();
			beginning = true;
			main();
		}
		window.draw(crd.credit_texts[14]);
		crd.music.setVolume(music_Volume / 10);
		window.display();
		crd.timer3 += clock.getElapsedTime().asSeconds();
	}
}



