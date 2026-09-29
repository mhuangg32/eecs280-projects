#include "TextBuffer.hpp"

// --- 构造函数 ---
//EFFECTS: Creates an empty text buffer. Its cursor is at the past-the-end
  //         position, with row 1, column 0, and index 0.
TextBuffer::TextBuffer() {
    cursor = data.end();
    row = 1;
    column = 0;
    index = 0;
}

// --- 光标左右移动 ---
bool TextBuffer::forward() {
    if(cursor == data.end()) return false;

    if(*cursor == '\n'){
        cursor++;
        row++;
        column = 0;
        index++;
        return true;
    }

    cursor++;
    column++;
    index++;
    return true;
}

bool TextBuffer::backward() {
    if(cursor == data.begin()) return false;

    cursor--;
    if(*cursor == '\n'){
        column = compute_column();
        row--;
    }
    else{
        column--;
    }

    index--;

    return true;
}

// --- 插入与删除 ---
void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    if(c == '\n'){
        column = 0;
        row++;
    }
    else{
        column++;
    }
    index++;

    return;
}

bool TextBuffer::remove() {
    if(cursor == data.end()){
        return false;
    }

    //char deletedChar = *cursor;
    cursor = data.erase(cursor);

    //if (deletedChar == '\n') {
    //    row--;
    //    column = compute_column();
    //}
    
    //index--;
    return true;
}

// --- 行内移动 ---
void TextBuffer::move_to_row_start() {
    while(column > 0){
        cursor--;
        column--;
        index--;
    }
    return;
}

void TextBuffer::move_to_row_end() {
    while(cursor != data.end() && *cursor != '\n'){
        cursor++;
        index++;
        column++;
    }
    return;
} 

void TextBuffer::move_to_column(int new_column) {
    if(column == new_column){
        return;
    }
    while(column < new_column){
        if(cursor == data.end() || *cursor == '\n') break;
        cursor++;
        index++;
        column++;
    }
    while(column > new_column){
        cursor--;
        index--;
        column--;
    }
    return;
}

// --- 跨行移动 ---
bool TextBuffer::up() {
    if(row == 1) return false;

    int targetCol = column;

    move_to_row_start();
    backward();
    move_to_column(targetCol);

    return true;
}

bool TextBuffer::down() {
    int targetCol = column;

    move_to_row_end();

    if(cursor == data.end()){
        move_to_column(targetCol);
        return false;
    }

    forward();
    move_to_column(targetCol);

    return true;
}

// --- 状态查询 (Getters) ---
bool TextBuffer::is_at_end() const {
    return cursor == data.end();
}

char TextBuffer::data_at_cursor() const {
    return *cursor; 
}

int TextBuffer::get_row() const {
    return row;
}

int TextBuffer::get_column() const {
    return column;
}

int TextBuffer::get_index() const {
    return index;
}

int TextBuffer::size() const {
    return data.size();
}

std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}

// --- 私有辅助函数 ---
int TextBuffer::compute_column() const {
    int cnt = 0;
    Iterator temp = cursor;
    while(temp != data.begin()){
        --temp;
        if(*temp == '\n') break;

        cnt++;
    }
    return cnt;
}