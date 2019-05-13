#include "Lock.h"
#include "LockSeg.h"
#include <string>
#include <vector>
#include <queue>

#include "definitions.h"

using namespace Gdiplus;
using namespace std;

Lock::Lock(void)
{
}


Lock::~Lock(void)
{
}

Lock::Lock(string home)
{
  proposition="((L&R)&(L&R)&!((L)|((L&R)&(L|R))))";
  x=0;
  y=0;
  width=LOCK_WIDTH;
  height=LOCK_HEIGHT;
  value=FALSE;
  num_segments=0;
  radius=width/2;

  

  //get the number of segments
  for(unsigned int j=0;j<proposition.size();j++)
  {
    //increment the segment counter
    if((proposition.at(j)=='L')||(proposition.at(j)=='R'))
    {
      num_segments++;
    }
  }
  
  //calculate the angles
  float angle=360.0f/num_segments;
  float half_angle=angle/2;
  float segment_angle=270;
  // put the proposition into the queue
  //and the segments into the vector
  for(unsigned int i=0;i<proposition.size();i++)
  {
    //increment the segment counter
    if((proposition.at(i)=='L')||(proposition.at(i)=='R'))
    {
      float start_angle=segment_angle;//-half_angle;//+angle;
      float end_angle=segment_angle+half_angle;
      
      int value=-1;
      if(i%2==0)
      {
        value=1;
      }

      //adjust for full circle
      if(start_angle<0)
      {
        start_angle=start_angle+360;
      }
      if(start_angle>=360)
      {
        start_angle=start_angle-360;
      }

      segments.push_back(LockSeg(LOCK_WIDTH/2,
                                 value,
                                 segment_angle,
                                 start_angle,
                                 angle));

      //increment the angle
      segment_angle=segment_angle+angle;

      //if our segment has an angle greater then 360
      //delete 360 off of it to bring us back in line.
      if(segment_angle>=360)
      {
        segment_angle=segment_angle-360;
      }
    }
    //add the current character to the queue
    prop.push(proposition.at(i));
  }
}

Lock::Lock(string p,
           vector<string> a,
           int new_x,
           int new_y,
           int new_width,
           int new_height,
           bool new_value)
{//Lock(...) starts
  proposition=p;
  solution=a;
  x=new_x;
  y=new_y;
  width=new_width;
  height=new_height;
  value=new_value;
  num_segments=0;
  radius=width/2;

  

  //get the number of segments
  for(unsigned int j=0;j<p.size();j++)
  {
    //increment the segment counter
    if((p.at(j)=='L')||(p.at(j)=='R'))
    {
      num_segments++;
    }
  }
  
  //calculate the angles
  float angle=360.0f/num_segments;
  float half_angle=angle/2;
  float segment_angle=270;
  // put the proposition into the queue
  //and the segments into the vector
  for(unsigned int i=0;i<p.size();i++)
  {
    //increment the segment counter
    if((p.at(i)=='L')||(p.at(i)=='R'))
    {
      float start_angle=segment_angle;//-half_angle;//+angle;
      float end_angle=segment_angle+half_angle;
      
      //adjust for full circle
      if(start_angle<0)
      {
        start_angle=start_angle+360;
      }
      if(start_angle>=360)
      {
        start_angle=start_angle-360;
      }

      segments.push_back(LockSeg(LOCK_WIDTH/2,
                                 0,
                                 segment_angle,
                                 start_angle,
                                 angle));

      //increment the angle
      segment_angle=segment_angle+angle;

      //if our segment has an angle greater then 360
      //delete 360 off of it to bring us back in line.
      if(segment_angle>=360)
      {
        segment_angle=segment_angle-360;
      }
    }
    //add the current character to the queue
    prop.push(p.at(i));
  }


}//Lock(...) ends

//getters and setters---------------------------------------------------
vector<string> Lock::get_soloution()
{
  return solution;
}

string Lock::get_proposition()
{//get_proposition() starts
  return proposition;
}//get_proposition() ends

int Lock::get_x()
{//get_x() starts
  return x;
}//get_x() ends

int Lock::get_y()
{//get_y() starts
  return y;
}//get_y() ends

int Lock::get_width()
{//get_width() starts
  return width;
}//get_width() ends

int Lock::get_height()
{//get_height() starts
  return height;
}//get_height() ends

float Lock::get_num_segments()
{//get_num_segments() Starts
  return num_segments;
}//get_num_segments() ends

vector<LockSeg> Lock::get_segments()
{//get_segments() starts
  return segments;
}//get_segments() ends

int Lock::get_value()
{//get_value() starts
  return value;
}//get_value() ends

float Lock::get_radius()
{//get_radius() starts
  return radius;
}//get_radius() ends

//setters
void Lock::set_proposition(string p)
{//set_proposition(...) starts
  proposition=p;
}//set_proposition(..) ends

void Lock::set_x(int new_x)
{//set_x(...) start
  x=new_x;
}//set_x(...) ends

void Lock::set_y(int new_y)
{//set_y(...) starts
  y=new_y;
}//set_y(...) ends

void Lock::set_width(int w)
{//set_width(...) starts
  width=w;
}//set_width(...) ends

void Lock::set_height(int h)
{//set_height(...) starts
  height=h;
}//set_height(...) ends

void Lock::set_num_segments(float s)
{//set_num_segments(...) starts
  num_segments=s;
}//set_num_segments(...) ends

void Lock::set_segments(vector<LockSeg> s)
{//set_segments(...) starts
  segments=s;
}//set_segments(...) ends

void Lock::set_value(int v)
{//set_value(...) starts
  value=v;
}//set_value(...) ends

void Lock::set_radius(float r)
{//set_radius(...) starts
  radius=r;
}//set_radius(...) ends

//Functions------------------------------------------------------------
void Lock::draw_lock(HDC hdc)
{//draw_lock(...) starts
  Graphics lock(hdc);
  Pen segment_pen(Color(255, 0, 0, 0),2);
  SolidBrush target_neutral(Color(255, 0, 0, 255));
  SolidBrush target_true(Color(255, 0, 255, 0));
  SolidBrush target_false(Color(255, 255, 0 ,0));
  SolidBrush target_back(Color(255, 25, 25, 25));
  //calculate the angle
  float angle=360.0f/num_segments;

  //create a float to hold the current angle
  float current_angle=0;


  //draw the segments
  
  
  //array of points for the segment lines
  PointF seperator[]={PointF(0,0),
                      PointF(0,-(width/2))};
  //======================================================================

  //loop through the segments drawing each one in turn
  for(unsigned int i=0;i<segments.size();i++)
  {
    //float seg_angle=segments.at(i).get_angle();
    float seg_start_angle=segments.at(i).get_start_angle();
    float seg_sweep=segments.at(i).get_sweep();
    Pen temp(Color(255, 0, 0, 0));
    switch(segments.at(i).get_value())
    {//switch(...) starts
    case -1:
      lock.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);
      ////draw the segment
      //lock.DrawLine(&temp, 0, 0, 0, 500);

      lock.FillPie(&target_false,
                   -LOCK_WIDTH/2,
                   -LOCK_HEIGHT/2,
                   LOCK_WIDTH,
                   LOCK_HEIGHT,
                   seg_start_angle,
                   seg_sweep);

      
      lock.DrawPie(&temp,
                   -LOCK_WIDTH/2,
                   -LOCK_HEIGHT/2,
                   LOCK_WIDTH,
                   LOCK_HEIGHT,
                   seg_start_angle,
                   seg_sweep);


      lock.TranslateTransform(-ORIGIN_X, -ORIGIN_Y, MatrixOrderAppend);
      break;
     
    case 0:
      lock.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);
      //if(i>0)
      //  break;

      //lock.DrawLine(&temp, 0, 0, 0, -500);
      ////draw the segment
      lock.FillPie(&target_neutral,
                   -LOCK_WIDTH/2,
                   -LOCK_HEIGHT/2,
                   LOCK_WIDTH,
                   LOCK_HEIGHT,
                   seg_start_angle,
                   seg_sweep);

      
      lock.DrawPie(&temp,
                   -LOCK_WIDTH/2,
                   -LOCK_HEIGHT/2,
                   LOCK_WIDTH,
                   LOCK_HEIGHT,
                   seg_start_angle,
                   seg_sweep);


      lock.TranslateTransform(-ORIGIN_X, -ORIGIN_Y, MatrixOrderAppend);
      break;

    case 1:
      lock.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);
      
      //lock.DrawLine(&temp, 0, 0, 0, -500);
      ////draw the segment
      lock.FillPie(&target_true,
                   -LOCK_WIDTH/2,
                   -LOCK_HEIGHT/2,
                   LOCK_WIDTH,
                   LOCK_HEIGHT,
                   seg_start_angle,
                   seg_sweep);

      
      lock.DrawPie(&temp,
                   -LOCK_WIDTH/2,
                   -LOCK_HEIGHT/2,
                   LOCK_WIDTH,
                   LOCK_HEIGHT,
                   seg_start_angle,
                   seg_sweep);


      lock.TranslateTransform(-ORIGIN_X, -ORIGIN_Y, MatrixOrderAppend);
      break;

    default:
      break;
    }//switch(...) ends
  }


  current_angle=0;
  //======================================================================
  for(int s=0;s<num_segments;s++)
  {
    //rotate to the right angle
    lock.RotateTransform(current_angle, MatrixOrderAppend);
    //draw the segment line
    
    lock.TranslateTransform(ORIGIN_X, ORIGIN_Y, MatrixOrderAppend);
    lock.DrawLines(&segment_pen, seperator, 2);
    lock.TranslateTransform(-ORIGIN_X, -ORIGIN_Y, MatrixOrderAppend);
    //rotate back to neutral
    lock.RotateTransform(-current_angle, MatrixOrderAppend);
    //increment the current angle
    current_angle=current_angle+angle;
  }
  //======================================================================

  //reset current angle to 0
  current_angle=0;
  //create a vector of the string that we can destroy
  vector<char> p;
  for(unsigned int k=0;k<proposition.size();k++)
  {
    p.push_back(proposition.at(k));
  }

  //send the vector to find symbols so we can draw them
  while(p.size()!=0)
  {
    //get our a working vector from find_symbols
    vector<char> pr=find_symbols(p);

    //chars to hold the current character and previous char
    char c= ' ';
    char pc=' ';
    //x position of the element
    int x_pos=0;
    //y position of the element
    int y_pos=0;
    //draw the symbols
    for(unsigned int l=0;l<pr.size();l++)
    {
      //get the current char
      c=pr.at(l);
      //if the preceding char was parethesis then check what the current char
      //is, if it is another parenthesis increment the y_pos

      if((pc=='(')||(pc==')'))
      {
        if((c=='(')||(c==')'))
        {
          //increment the y_pos value
          y_pos++;
          x_pos=0;
        }
        
        //0 the x pos
        x_pos=0;
      }

      //Perform the draw
      draw_symbol(hdc, pr.at(l), x_pos, y_pos, current_angle);
      
      //increment the x_pos;
      x_pos++;
      //set the current char to the previous char
      pc=c;

    }
    //re-set the x and y pos
    x_pos=0;
    y_pos=0;
    //increment the current angle
    current_angle=current_angle+angle;
    //trim p by the size of of the working vector to remove the symbols
    //we are going to display
    p.erase(p.begin(), p.begin()+pr.size());
  }
}//draw_lock(...) ends



void Lock::draw_symbol(HDC hdc, char s, int x_pos, int y_pos, float r)
{//draw_symbol(...) starts
  //Graphics symbol(*hdc);
  Graphics symbol(hdc);
  Pen symbol_pen(Color(255, 255, 255, 0), 3);
  int level=0;
  int bracket_level=0;

  //symbol.RotateTransform(orientation-angle, MatrixOrderAppend);
  
  Pen pen(Color(255, 0, 255, 0), 3);
  //symbol.DrawLine(&pen, 0,0, 0,500);
  //set the viewport for the next operation
  SetViewportOrgEx(hdc, ORIGIN_X, ORIGIN_Y, NULL);

  switch(s)
  {//switch(symbol) starts
  case '&':
    {
      level=x_pos*SYMBOL_SPACING;
      //rotate to the correct angle
      PointF and[]={
        PointF(0,-radius-11-level),
        PointF(10,-radius-1-level),
        PointF(0,-radius-11-level),
        PointF(-10,-radius-1-level)
        };
      symbol.RotateTransform(r, MatrixOrderAppend);
      symbol.DrawLines(&symbol_pen, and, 4);
      symbol.RotateTransform(-r, MatrixOrderAppend);
    }
    break;

  case '|':
    {
      level=x_pos*SYMBOL_SPACING;
      PointF or[]={
        PointF(10,-radius-11-level),
        PointF(0,-radius-1-level),
        PointF(-10,-radius-11-level),
        PointF(0,-radius-1-level)};
      //rotate to the correct angle
      symbol.RotateTransform(r, MatrixOrderAppend);
      symbol.DrawLines(&symbol_pen, or, 4);
      symbol.RotateTransform(-r, MatrixOrderAppend);
    }
    break;

  case '!':
    {
      level=x_pos*SYMBOL_SPACING;
      //rotate to the correct angle
      symbol.RotateTransform(r, MatrixOrderAppend);
      symbol.DrawLine(&symbol_pen,
                      10.0f,
                      -radius-5.0f-level,
                      -10.0f,
                      -radius-5.0f-level);
      symbol.RotateTransform(-r, MatrixOrderAppend);
    }
    break;

  case '(':
    {
      level=x_pos*SYMBOL_SPACING;
      bracket_level=y_pos*BRACKET_LEVEL;
      PointF open[]={
        PointF(8+bracket_level, -radius+level),
        PointF(0+bracket_level, -radius+level),
        PointF(0+bracket_level, -radius+15+level),
        PointF(8+bracket_level, -radius+15+level)};
      symbol.RotateTransform(r, MatrixOrderAppend);
      symbol.DrawBeziers(&symbol_pen, open, 4);
      symbol.RotateTransform(-r, MatrixOrderAppend);
    }
    break;

  case ')':
    {
      level=x_pos*SYMBOL_SPACING;

      PointF close[]={
        PointF(-8-bracket_level, -radius+level),
        PointF(0-bracket_level, -radius+level),
        PointF(0-bracket_level, -radius+15+level),
        PointF(-8-bracket_level, -radius+15+level)};
      symbol.RotateTransform(r, MatrixOrderAppend);
      symbol.DrawBeziers(&symbol_pen, close, 4);
      symbol.RotateTransform(-r, MatrixOrderAppend);
    }
    break;

  default:
    break;
  }//switch(symbol) Ends

}//draw_symbol(...) ends


vector<char> Lock::find_symbols(vector<char> p)
{//add_segment(...) starts
  char c=' ';
  int pos=0;
  int size=p.size();
  vector<char> elements;

  for(int i=0;i<=size;i++)
  {
    if((p.size()==1)||(i==(p.size()-1)))
    {
      c=p.at(i);
      //add element to vector
      elements.push_back(c);
      //return 
      return elements;
    }
    else
    {
      c=p.at(i);
      if((c=='L')||(c=='R'))
      {
        elements.push_back(c);
        return elements;
      }
      else
      {
        elements.push_back(c);
      }
    }
  }
  return elements;
}//add_segment(...) ends


//the following code is a recursive decent parser to check the logic
//at this time it is untested. (saturday 19:35 hours);

//reads the values of all the segments, compares it to the proposition
//and determines if it is true or false
int Lock::evaluate(queue<char> prop, int pos)
{//check_result() starts
  //current char
  char c=' ';

  //left/symbol/right values
  int left=2;
  char symbol=' ';
  int right=2;

  //final result value
  int result=-1;

  
  //check to see if we need to evaluate the expression
  if(check_evaluate(right, left, symbol))
  {
    //if we need to evaluate the expression, do so
    //and set result to the right outcome
    switch(evaluate_single_expression(left, right, symbol))
    {
    case -1:
      result=-1;
      break;
      
    case 0:
      result=0;
      break;

    case 1:
      result=1;
      break;
      
    default:
      result=0;
      break;
    }
  }

  //Loop through the queue...
  for(unsigned int i=0;i<prop.size();i++)
  {
    //get the next element to be parsed
    c=prop.front();

    //pop the queue
    prop.pop();

    //evaluate pairs of expressions
    switch(c)
    {
    //if we have an opening bracket then check if we are in the 
    //left or right of the equation and perform recursion.
    case '(':
      {
        //if the left side is null that is what we are building
        if(left==2)
        {
          //recursive call to evaluate the left hand side
          left=evaluate(prop, pos);
        }
        //otherwise it is the right side
        else
        {
          //recursive call to evaluate the right hand side
          right=evaluate(prop, pos);
        }
      }
      break;

    //if we have an L then get the value of the segment
    case 'L':
      {
        //get the value from the segment
        left=segments.at(0).get_value();
        //increase the segment counter
        pos++;
      }
      break;

    //if we have an R then get the value of the segment
    case 'R':
      {
        //get the value from the segment
        right=segments.at(0).get_value();
        //increase the segment counter
        pos++;
      }
      break;

    //if we have a closing parenthesis, return our calcualted result
    case ')':
      return result;
      break;
    
    //if we have an & then set the symbol
    case '&':
      symbol='&';
      break;

    //if we have a | then set the symbol
    case '|':
      symbol='|';
      break;

    //if we have a ! then set the symbol
    case '!':
      symbol='!';
      break;

    //default return false
    default:
      return -1;
      break;
    }
  }
  return result;
}//check_resutl() ends


/**
* Function:    get_segment(int right, int left, char symbol)
* Description: check to see if we need to evaluate an expression
*/
bool Lock::check_evaluate(int right, int left, char symbol)
{//check_evaluate(...) starts
  switch(symbol)
  {//switch(symbol starts)
  case ' ':
    return FALSE;
    break;

    //if we have a NOT, check that we have at least one value to negate
  case '!':
    if((left==2)&&(right==2))
    {
      return FALSE;
    }
    else
    {
      return TRUE;
    }
    break;

    //if we have an AND, check that we have 2 values to compare
  case '&':
    if((left!=2)&&(right!=2))
    {
      return TRUE;
    }
    else
    {
      return FALSE;
    }
    break;

    //if we have an OR, check that we have 2 values to compare
  case '|':
    if((left!=2)&&(right!=2))
    {
      return FALSE;
    }
    else
    {
      return TRUE;
    }
    break;

    //default return false
  default:
      return FALSE;
    break;
  }//switch(symbol ends

  //return false in case everything fails...
  return FALSE;
}//check_evaluate(...) ends

//check a single expression
int Lock::evaluate_single_expression(int right, int left, char symbol)
{//check_single_expression(...) starts
  switch(symbol)
  {//switch(symbol) starts

    //we have an AND
    case '&':
      if((right==1)&&(left==1))
      {
        return 1;
      }
      else if((left==0)||(right==0))
      {
        return 0;
      }
      else
      {
        return -1;
      }
      break;

    //we have an OR
    case '|':
      if((right==1)||(left==1))
      {
        return 1;
      }
      else
      {
        return -1;
      }
      break;

    //we have a NOT
    case '!':
      if((right==0)&&(left==0))
      {
        return 0;
      }
      else if((left==1)||(right==1))
      {
        return -1;
      }
      else if((left==-1)||(right==-1))
      {
        return 1;
      }
      else
      {
        return 0;
      }
      break;

    default:
      return 0;
      break;
  }//switch(symbol) ends
}//check_single_espression(...) ends

bool Lock::simple_check()
{
  string cur;
  for(unsigned int i=0;i<segments.size();i++)
  {
    int v=segments.at(i).get_value();
    switch(v)
    {
    case -1:
      cur.push_back('F');
      break;
    case 1:
      cur.push_back('T');
      break;
    default:
      return FALSE;
      break;
    }
  }

  //compare against the possible answers
  for(unsigned int j=0;j<solution.size();j++)
  {
    string test=solution.at(j);
    for(unsigned int k=0;k<test.size();k++)
    {
    
      if(!(cur.at(k)==test.at(k)))
      {
        return FALSE;
      }
      if(k==(test.size()-1))
      {
        return TRUE;
      }
    }
  }

  //if we reach the end without success return false
  return TRUE;
}