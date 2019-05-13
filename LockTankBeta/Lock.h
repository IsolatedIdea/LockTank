#pragma once
#include <vector>
#include <queue>
#include <string.h>
#include "LockSeg.h"

using namespace std;

class Lock
{
private:
  string proposition;
  vector<string> solution;
  queue<char> prop;
  int x;
  int y;
  int width;
  int height;
  float radius;
  float num_segments;
  vector<LockSeg> segments;
  int value;

  
  bool check_evaluate(int right, int left, char symbol);
  int evaluate_single_expression(int right, int left, char symbol);
  LockSeg build_segment(int pos,
                        float angle,
                        vector<char> elements);
  vector<char> find_symbols(vector<char> p);
  void draw_symbol(HDC hdc, char s, int x_pos, int y_pos, float r);

public:
  Lock(void);
  ~Lock(void);

  Lock(string home);

  Lock(string func,
       vector<string> answer,
       int new_x,
       int new_y,
       int new_width,
       int new_height,
       bool new_value);

  //getters and setters
  int get_x();
  int get_y();
  int get_width();
  int get_height();
  float get_radius();
  float get_num_segments();
  string get_proposition();
  vector<LockSeg> get_segments();
  int get_value();
  vector<string> get_soloution();

  void set_proposition(string p);
  void set_x(int new_x);
  void set_y(int new_y);
  void set_width(int w);
  void set_height(int h);
  void set_radius(float r);
  void set_num_segments(float s);
  void set_segments(vector<LockSeg> s);
  void set_value(int v);

  //Functions
  void draw_lock(HDC hdc);
  int evaluate(queue<char> prop, int pos);
  int get_segment_value(int pos);
  vector<char> get_proposition(queue<char> p);

  bool simple_check();
};

