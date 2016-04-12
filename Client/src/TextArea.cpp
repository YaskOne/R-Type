#include "TextArea.h"

TextArea::TextArea(Font const& font, sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& defaultText)
{
	_font = ac->getFont(font);
	_pos = pos;
	_size = size;
	_textArea = new sf::RectangleShape(_size);
	_textArea->setPosition(_pos);
	_textArea->setFillColor(sf::Color(76, 157, 172));
	_defaultText = defaultText;
	_text = _defaultText;
	_drawableText = new sf::Text;
	_drawableText->setFont(*_font);
	_drawableText->setPosition(_pos.x + 5, _pos.y + 5);
}

void TextArea::update(keyboardStatus status)
{
	char entry;

	if (cursorOnIt(status.mousePos))
	{
		_textArea->setFillColor(sf::Color(171, 76, 172));
		entry = status.textEntered;
		if (_text.size() == 0)
			_text = _defaultText;
		if (entry != -1)
		{
			if (_text == _defaultText)
				_text = "";
			if (entry == '\b' && _text.size() != 0)
				_text.pop_back();
			else if (entry != '\b')
				_text += entry;
		}
	}
	else
		_textArea->setFillColor(sf::Color(76, 157, 172));
	_drawableText->setString(_text);
}

sf::Drawable * TextArea::getTextArea()
{
	return _textArea;
}

std::string TextArea::getText()
{
  return _text;
}

sf::Text * TextArea::getDrawableText()
{
	return _drawableText;
}

bool TextArea::cursorOnIt(sf::Vector2i const& mousepos)
{
	if (
		mousepos.x > _pos.x &&
		mousepos.y > _pos.y &&
		mousepos.x < (_pos.x + _size.x) &&
		mousepos.y < (_pos.y + _size.y)
		)
		return true;
	return false;
}
