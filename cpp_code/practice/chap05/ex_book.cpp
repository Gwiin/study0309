#include <iostream>
#include <cstring>

using namespace std;

class Book{
private:
    double price;
    int pages;
    char *title;
    char *author;
public:
    Book(double pr, int pa, char *t, char *a);
    Book(const Book &book);
    ~Book();

    void changeBook(const char *title, const char *author, int page, int price);
    void show();
};

Book::Book(double pr, int pa, char *t, char *a){
    this->price = pr;
    this->pages = pa;
    int len = strlen(t);
    this->title = new char [len+1];
    len = strlen(a);
    this->author = new char [len+1];
    strcpy(this->title,t);
    strcpy(this->author,a);
}

Book::Book(const Book &book){
    this->price = book.price;
    this->pages = book.pages;
    int len = strlen(book.title);
    this->title = new char [len+1];
    len = strlen(book.author);
    this->author = new char [len+1];
    strcpy(this->title, book.title);
    strcpy(this->author, book.author);

    cout << "복사생성자 실행. 원본객체의 title : " << this->title << ", author : " << this->author << endl;
    cout << endl;
}

Book::~Book(){
    if(this->title){
        cout << title << " 할당 해제" << endl;
        delete [] title;
    }
    if(author){
        cout << author << " 할당 해제" << endl;
        delete [] author;
    }
}

void Book::changeBook(const char *title, const char *author, int page, int price){
    if(strlen(title) > strlen(this->title)){
        return;
    }
    strcpy(this->title, title);

    if(strlen(author) > strlen(this->author)){
        return;
    }
    strcpy(this->author, author);

    this->pages = page;
    this->price = price;
}



void Book::show(){
    cout << "TITLE : " << this->title << endl;
    cout << "AUTHOR : " << this->author << endl;
    cout << "PAGES : " << this->pages << " pages" <<  endl;
    cout << "PRICE : " << this->price << "원" << endl;
    cout << endl;
}




int main(void){
    Book c(26000, 655, "혼자 공부하는 C언어", "서현우");
    Book cpp(c);

    cout << "c 객체 생성 직후----" << endl;

    cout << "c.show()" << endl;
    c.show();
    cout << "cpp.show()" << endl;
    cpp.show();

    cpp.changeBook("C++ 프로그래밍", "황기태", 690, 34000);

    cout << "cpp Book 변경 -------------------------" << endl;
    cout << "c.show()" << endl;
    c.show();
    cout << "cpp.show()" << endl;
    cpp.show();  

    return 0;
    
}