#pragma once
#include <Arduino.h>
#include <vector>
#include "HtmlTagHelper.h"


// ✅ Common HTML Tags
String HtmlDiv(const String& content, const String& attributes = "");
String HtmlSpan(const String& content, const String& attributes = "");
String HtmlParagraph(const String& content, const String& attributes = "");
String HtmlHeader(int level, const String& content, const String& attributes = ""); // h1-h6
String HtmlSection(const String& content, const String& attributes = "");
String HtmlArticle(const String& content, const String& attributes = "");
String HtmlLabel(const String& content, const String& attributes = "");
String HtmlForm(const String& content, const String& attributes = "");
String HtmlButton(const String& content, const String& attributes = "");
String HtmlLink(const String& href, const String& text, const String& attributes = "");
String HtmlImage(const String& src, const String& attributes = "");
String HtmlInput(const String& attributes = "");
String HtmlTextarea(const String& content, const String& attributes = "");
String HtmlSelect(const String& content, const String& attributes = "");
String HtmlOption(const String& content, const String& attributes = "");
String HtmlBr();
String HtmlHr();
