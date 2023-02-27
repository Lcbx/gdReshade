#ifndef GDRESHADE_H
#define GDRESHADE_H

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class gdReshade : public Sprite2D {
    GDCLASS(gdReshade, Sprite2D)

private:
	float time_passed;
    float speed;
    const float amplitude = 11.0;
	
protected:
	
	static void _bind_methods(){
		ClassDB::bind_method(D_METHOD("get_speed"), &gdReshade::get_speed);
		ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &gdReshade::set_speed);
		ClassDB::add_property("gdReshade", PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed");
	}
	
	void set_speed(float p_speed) {
		speed = p_speed;
	}

	float get_speed() const {
		return speed;
	}

public:
    gdReshade(){
		// initialize any variables here
		time_passed = 0.0;
		speed = 2.0;
	}
    ~gdReshade(){
		// add your cleanup here
	}

    void _process(float delta){
		time_passed += delta;

		Vector2 new_position = Vector2(amplitude * sin(time_passed * speed), amplitude * cos(time_passed * speed));

		set_position(new_position);
	}
};

}

#endif