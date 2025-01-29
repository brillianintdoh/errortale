#ifndef BattleNode_H
#define BattleNode_H
#include "../heartNode/heartNode.h"
#include "../attack/sansBone/sansBone.h"
#include<functional>
#include<godot_cpp/classes/node2d.hpp>
#include<godot_cpp/classes/animated_sprite2d.hpp>
#include<godot_cpp/classes/texture_rect.hpp>
#include<godot_cpp/variant/dictionary.hpp>
#include<godot_cpp/classes/texture_progress_bar.hpp>
#include<godot_cpp/classes/label.hpp>
#include<godot_cpp/classes/noise_texture2d.hpp>
#include<godot_cpp/classes/control.hpp>
#include<godot_cpp/classes/rich_text_label.hpp>
#include<godot_cpp/classes/shader_material.hpp>
#include<godot_cpp/classes/item_list.hpp>
using namespace std;
namespace godot {
    class BattleNode : public Node2D {
        GDCLASS(BattleNode, Node2D);

        protected:
            static void _bind_methods();

        private:
            Dictionary audio, music, db;
            vector<Ref<Texture2D>> btn;
            vector<Ref<Texture2D>> btnON;
            AnimatedSprite2D* sans;
            TextureRect* background;
            TextureRect* shader;
            HeartNode* heart;
            Node2D* sprite;
            Node2D* buttons;
            Control* clipRect;
            Sprite2D* frame;
            TextureProgressBar* hpBar;
            TextureProgressBar* KR;
            Ref<NoiseTexture2D> KR_progress;
            Ref<ShaderMaterial> material;
            Label* hpText;
            RichTextLabel* menu_text;
            ItemList* item_list;
            Array json_text, json_item;
            vector<Vector2> frameVecs;
            vector<Node2D*> songs;
            int isSong;

            double times, cool, time_KARMA;
            int is, isAttack, isSelect, isMoveButton, part;
        
        public:
            BattleNode();
            ~BattleNode();

            void _process(double delta) override;
            void _ready() override;

            // _process 함수의 loop 함수
            void effects(double delta);

            // effects 함수
            void camera_shake(double cool, float stre=0.5, float dur=0.3, function<void()> fun=[](){});
            void camera_angle(double angle=0, double speed=1.3);
            void blackScene(double cool, function<void()> fun=[](){});
            void set_frame(Vector2 vec, int type, function<void()> fun=[](){}, double speed=1);
            void set_shader(double cool, double shake_power=0.03, double shake_rate=0.2, double speed=5, double color_rate=0.01);
            void sleep(function<void()> fun, double cool);
            void loop(function<int(double delta)> fun);

            // 기본함수
            void init();
            void start(double delta);
            void nextTurn();

            // finished 함수
            void animated_start_end();
            void music_next();
            void attack_end();
            void song_loop();

            // sprite 함수
            void set_gasterBlaster(Vector2 pos, Vector2 scale, float angle, float cool=3, int isLaunch=true);
            void set_bone1(Vector2 pos, Vector2 target, Vector2 scale, float angle=0, float speed=1);
            SansBone* set_bone2(Vector2 pos, Vector2 target, Vector2 scale, float angle=0, float speed=1, int is=false);
            void set_bone3(Vector2 pos, Vector2 scale, double cool=10, float angle=0, float speed=0.2);

            // part 함수
            void game(double delta);
            void part1(double delta);
            void part2(double delta);

            // menu 함수
            void menu_1();
            void menu_3();
            void use_3();
            void update_menu3();
    };
}

#endif