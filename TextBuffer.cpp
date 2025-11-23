#include "TextBuffer.hpp"

TextBuffer::TextBuffer()
    : data(),
      cursor(data.end()),
      row(1),
      column(0),
      index(0)
{
}

bool TextBuffer::forward()
{
  if (cursor == data.end())
    return false;
  char c = *cursor;
  ++cursor;
  ++index;
  if (c == '\n')
  {
    ++row;
    column = 0;
  }
  else
  {
    ++column;
  }
  return true;
}

bool TextBuffer::backward()
{
  if (cursor == data.begin())
    return false;
  --cursor;
  --index;
  if (*cursor == '\n')
  {
    --row;
    column = compute_column();
  }
  else
  {
    --column;
  }
  return true;
}

void TextBuffer::insert(char c)
{
  cursor = data.insert(cursor, c);
  ++cursor;
  ++index;
  if (c == '\n')
  {
    ++row;
    column = 0;
  }
  else
  {
    ++column;
  }
}

bool TextBuffer::remove()
{
  if (cursor == data.end())
    return false;
  char c = *cursor;
  auto next = data.erase(cursor);
  cursor = next;
  index = (cursor == data.end() ? data.size() : index);
  if (c == '\n')
    column = compute_column();
  return true;
}

void TextBuffer::move_to_row_start()
{
  while (cursor != data.begin())
  {
    auto prev = cursor;
    --prev;
    if (*prev == '\n')
      break;
    backward();
  }
  column = 0;
  index = get_index();
}

void TextBuffer::move_to_row_end()
{
  auto it = cursor;
  while (it != data.end() && *it != '\n')
    ++it;
  cursor = it;
  index = get_index();
  column = compute_column();
}

void TextBuffer::move_to_column(int new_column)
{
  move_to_row_start();
  int count = 0;
  while (cursor != data.end() && *cursor != '\n' && count < new_column)
  {
    forward();
    ++count;
  }
}

bool TextBuffer::up()
{
  if (row == 1)
    return false;
  int target = column;
  move_to_row_start();
  if (!backward())
    return false;
  while (cursor != data.begin() && *cursor != '\n')
    backward();
  if (*cursor == '\n')
    forward();
  int c = target;
  while (cursor != data.end() && *cursor != '\n' && c > 0)
  {
    forward();
    --c;
  }
  return true;
}

bool TextBuffer::down()
{
  auto it = cursor;
  while (it != data.end() && *it != '\n')
    ++it;
  if (it == data.end())
    return false;
  ++it;
  if (it == data.end())
    return false;
  int target = column;
  cursor = it;
  ++row;
  column = 0;
  index = get_index();
  while (cursor != data.end() && *cursor != '\n' && target > 0)
  {
    forward();
    --target;
  }
  return true;
}

bool TextBuffer::is_at_end() const
{
  return cursor == data.end();
}

char TextBuffer::data_at_cursor() const
{
  return *cursor;
}

int TextBuffer::get_row() const { return row; }
int TextBuffer::get_column() const { return column; }
int TextBuffer::get_index() const { return index; }
int TextBuffer::size() const { return data.size(); }

std::string TextBuffer::stringify() const
{
  return std::string(data.begin(), data.end());
}

int TextBuffer::compute_column() const
{
  int col = 0;
  auto it = cursor;

  if (it == data.end())
  {
    if (data.empty())
      return 0;
    it = data.end();
    --it;
    if (*it == '\n')
      return 0;
    while (it != data.begin())
    {
      auto prev = it;
      --prev;
      if (*prev == '\n')
        break;
      ++col;
      it = prev;
    }
    return col + 1;
  }

  while (it != data.begin())
  {
    auto prev = it;
    --prev;
    if (*prev == '\n')
      break;
    ++col;
    it = prev;
  }

  return col;
}
