#ifndef BattleNode_H
#define BattleNode_H
#include<godot_cpp/classes/node2d.hpp>
namespace godot {
    class BattleNode : public Node2D {
        GDCLASS(BattleNode, Node2D);

        protected:
            static void _bind_methods();
        
        public:
            BattleNode();
            ~BattleNode();

            void _process(double delta) override;
            void _ready() override;
    };
}

#endif