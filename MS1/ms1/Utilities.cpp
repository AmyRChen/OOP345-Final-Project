// Name: PingJu, Chen
// Seneca Student ID: 151043205
// Seneca email: pchen72@myseneca.ca
// Date of completion: TBA
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;
namespace sdds {
   //Class variable initialize
   char Utilities::m_delimiter{};

   void Utilities::setFieldWidth(size_t newWidth){
      m_widthField = newWidth;
   }

   size_t Utilities::getFieldWidth() const{
      return m_widthField;
   }

   std::string Utilities::extractToken(
      const std::string& str, size_t& next_pos, bool& more) {
      std::string token{};
      if (more) {
         token = trim(str.substr(next_pos, (str.find(m_delimiter, next_pos) - next_pos)));
         m_widthField < token.length() ? m_widthField = token.length() : m_widthField;

         if (str.find(m_delimiter, next_pos) != string::npos && !token.empty()) {
            next_pos = str.find(m_delimiter, next_pos) + 1;
            more = true;
            return token;  //Fix: Hello
         }
         else {
            more = false;
         }

         //Check delemiter 
         if (str[next_pos] == m_delimiter) {
            throw std::string("ERROR: Delimiter is found at next position!");
         }
         return token;
      }
   }

   void Utilities::setDelimiter(char newDelimiter){
      m_delimiter = newDelimiter;
   }

   char Utilities::getDelimiter(){
      return m_delimiter;
   }

   std::string trim(const std::string& str){
      std::string temp{};
      if (!str.empty()) {
         temp = str;
         temp.erase(0, temp.find_first_not_of(" "));
         temp.erase(temp.find_last_not_of(" ") + 1);
      }
      return temp;
   }

}