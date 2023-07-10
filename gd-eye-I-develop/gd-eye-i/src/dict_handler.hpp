
#ifndef DICTHANDLER_H
#define DICTHANDLER_H

#include "JSONHandler.h"
#include <stdint.h>
#include <float.h>
#include <string>
#include <algorithm>

extern "C"
  {
#include "o_integer.h"
#include "rational.h"
#include "unicode.h"
  };
#include "godot_cpp/godot.hpp"
#include "logger.hpp"

class GodotDictionaryHandler : public JSONHandler
  {
  private:
  struct Node
  {
    Node* parent;
    virtual ~Node() {}
  };
   struct DictionaryNode : public Node
   {
      godot::Dictionary dictionary;   
   };

   struct ArrayNode : public Node
   {
      godot::Array array;
   };
  protected:
    std::vector<DictionaryNode*> dictionary_nodes {50};
    std::vector<ArrayNode*> array_nodes {50};
    Node* current_node_ptr {nullptr};
    DictionaryNode* root_node {nullptr};
    godot::String current_pair_name;

  public:
    GodotDictionaryHandler(void)  { }
    ~GodotDictionaryHandler(void)  {reset(); } 
    godot::Dictionary get_dictionary() {return root_node->dictionary;}
    virtual void true_value(void) override 
    { 
      add_to_current(true);
    }
    
    virtual void false_value(void) override 
    { 
      add_to_current(false);
    }
    virtual void boolean_value(bool to_write) override 
    { 
      add_to_current(to_write);
    }
    virtual void null_value(void) override 
    {
      add_to_current(nullptr); 
    }
    virtual void string_value(const char *to_write) override 
    { 
      add_to_current(to_write);
    }
    virtual void string_value(const std::string &to_write) override 
    { 
      add_to_current(to_write.c_str());
    }
    virtual void number_value(int to_write) override 
    { 
      add_to_current(to_write);
    }
    virtual void number_value(unsigned int to_write) override 
    { 
      add_to_current(to_write);
    }
    virtual void number_value(long to_write) override 
    { 
      add_to_current(to_write);
    }
    virtual void number_value(unsigned long to_write) override 
    { 
      add_to_current(to_write);
    }
    virtual void number_value(o_integer to_write) override 
    { 
      add_to_current(to_write.the_long);
    }
    virtual void number_value(double to_write, int precision) override 
    { 
      add_to_current(to_write);
    }
    virtual void number_value(double to_write) override
      { number_value(to_write, DBL_DIG); }
    virtual void number_value(o_integer mantissa_whole_part,
            o_integer mantissa_fraction_numerator,
            size_t mantissa_fraction_digit_count, o_integer exponent) override { }
    virtual void number_value(const char *number_text) override { }
    virtual void start_object(void) override 
    {
      DictionaryNode* new_object = new DictionaryNode();
      new_object->parent = current_node_ptr;
      dictionary_nodes.push_back(new_object);
      auto it = dictionary_nodes.end() - 1;
      if (current_node_ptr == nullptr)
      {
        root_node = *it;
        current_node_ptr = root_node;
      }
      else
      {
        add_to_current(new_object->dictionary);
        current_node_ptr = *it;
       
      }
    }
    virtual void finish_object(void) override 
    {
      current_node_ptr = current_node_ptr->parent;
    }
    virtual void start_pair(const char *name) override 
    { 
      current_pair_name = godot::String(name);
    }
    virtual void pair(const char *name, const char *string_value)  override 
    {
      current_pair_name = godot::String(name);
      add_to_current(string_value);
    }
    virtual void pair(const char *name, const std::string &string_value) override 
    {
      current_pair_name = godot::String(name);
      add_to_current(string_value.c_str());
    }
    virtual void pair(const char *name, bool value) override 
    {
      current_pair_name = godot::String(name);
      add_to_current(value);
    }
    virtual void pair(const char *name, int value) override 
    {
      current_pair_name = godot::String(name);
      add_to_current(value); 
    }
    virtual void pair(const char *name, unsigned int value)  override
    {
      current_pair_name = godot::String(name);
      add_to_current(value); 
    }
    virtual void pair(const char *name, long value) override 
    {
      current_pair_name = godot::String(name);
      add_to_current(value);;  
    }
    virtual void pair(const char *name, unsigned long value) override 
    {
      current_pair_name = godot::String(name);
      add_to_current(value); 
    }
    virtual void pair(const char *name, double value, int precision)  override
    {
      current_pair_name = godot::String(name);
      add_to_current(value); 
    }
    virtual void pair(const char *name, double value) override
      { pair(name, value, DBL_DIG); }
    
    virtual void start_array(void) override 
    {
        auto array = new ArrayNode();
        array->parent = current_node_ptr;
        array_nodes.push_back(array);
        add_to_current(array->array);
        current_node_ptr = array;
    }
    virtual void finish_array(void) override 
    {
      current_node_ptr = current_node_ptr->parent;
    }

    virtual void reset(void) override 
    {
      std::for_each(dictionary_nodes.begin(), dictionary_nodes.end(), [](DictionaryNode* n){delete n;});
      std::for_each(array_nodes.begin(), array_nodes.end(), [](ArrayNode* n){delete n;});
      dictionary_nodes.clear();
      array_nodes.clear();
      current_node_ptr = nullptr;
      root_node = nullptr;
    }

    void add_to_current(const godot::Variant& value)
    {
      auto* an = dynamic_cast<ArrayNode*>(current_node_ptr);
      auto* dn = dynamic_cast<DictionaryNode*>(current_node_ptr);
      if (an != nullptr) 
      {
        an->array.append(value);
      }
      else if (dn != nullptr)
      {
        dn->dictionary[current_pair_name] = value; 
      }
    }
    virtual void sort_keys(void) override { }



  };

#endif