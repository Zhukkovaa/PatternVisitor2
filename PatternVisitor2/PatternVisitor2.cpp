#include <iostream>
#include <vector>

// Объявление трех классов(предварительное описание): Лекция, Лабораторное занятие, Семинар
class Lecture;
class Lab;
class Seminar;

// Абстрактный класс Занятие
class Lesson {// базовый класс-элемент
public:
    virtual void accept(class Visitor& v) = 0;
    virtual ~Lesson() {}//виртуальный деструктор
};

// Класс Лекция
class Lecture : public Lesson {//конкретный класс-элемент
public:
    Lecture(int hours, int max_score) : hours_(hours), max_score_(max_score) {}//конструктор
    virtual ~Lecture() {}//виртуальный декструктор
    // Переопределенный метод accept, принимающий объект Visitor по ссылке и не возвращающий никакого значения
    // Этот метод будет вызываться у Visitor, передавая в него this (текущий объект Lecture)
    void accept(Visitor& v) override;
    int hours_;// количество часов
    int max_score_;// максимальное количество баллов
};

// Класс Лабораторное занятие
class Lab : public Lesson {
public:
    Lab(int hours, int max_score) : hours_(hours), max_score_(max_score) {}
    virtual ~Lab() {}
    void accept(Visitor& v) override;
    int hours_;
    int max_score_;
};

// Класс Семинар
class Seminar : public Lesson {
public:
    Seminar(int hours, int max_score) : hours_(hours), max_score_(max_score) {}
    virtual ~Seminar() {}
    void accept(Visitor& v) override;
    int hours_;
    int max_score_;
};


// Абстрактный класс Visitor
class Visitor {
public:
    // Виртуальная функция visit для посещения лекции,
    // которая должна быть реализована в производных классах
    virtual void visit(Lecture& lecture) = 0;
    // Виртуальная функция visit для посещения лабораторной работы,
    // которая должна быть реализована в производных классах
    virtual void visit(Lab& lab) = 0;
    // Виртуальная функция visit для посещения семинара,
    // которая должна быть реализована в производных классах
    virtual void visit(Seminar& seminar) = 0;
};

// Класс Предмет
class Subject {
public:
    // конструктор класса, который принимает ссылку на вектор указателей на объекты типа Lesson и инициализирует соответствующий член класса lessons_
    Subject(std::vector<Lesson*>& lessons) : lessons_(lessons) {}
    void accept(Visitor& v) {// объявление публичного метода accept, который принимает объект типа Visitor по ссылке
        for (auto lesson : lessons_) {
            lesson->accept(v);//вызов метода accept для текущего объекта типа Lesson, передавая ему объект типа Visitor
        }
    }
private:
    std::vector<Lesson*> lessons_;// вектор указателей на объекты типа Lesson, хранящийся в классе
};

// Класс HourCounterVisitor
class HourCounterVisitor : public Visitor {
public:
    // Определение публичных переменных, которые будут содержать суммарное количество часов для каждого типа урока
    int total_lecture_hours;
    int total_lab_hours;
    int total_seminar_hours;

    HourCounterVisitor() : total_lecture_hours(0), total_lab_hours(0), total_seminar_hours(0) {}//конструктор
    // Определение функции visit, которая принимает объект класса Lecture и переопределяет чисто виртуальную функцию из базового класса Visitor
    void visit(Lecture& lecture) override { total_lecture_hours += lecture.hours_; }// Увеличение значения переменной на количество часов в лекции
    void visit(Lab& lab) override { total_lab_hours += lab.hours_; }
    void visit(Seminar& seminar) override { total_seminar_hours += seminar.hours_; }
};

// Класс ScoreCounterVisitor
class ScoreCounterVisitor : public Visitor {
public:
    int lecture_max_score_;
    int lab_max_score_;
    int seminar_max_score_;
    ScoreCounterVisitor() : lecture_max_score_(0), lab_max_score_(0), seminar_max_score_(0) {}
    void visit(Lecture& lecture) override {
        if (lecture.max_score_ > lecture_max_score_) {
            lecture_max_score_ = lecture.max_score_;
        }
    }
    void visit(Lab& lab) override {
        if (lab.max_score_ > lab_max_score_) {
            lab_max_score_ = lab.max_score_;
        }
    }
    void visit(Seminar& seminar) override {
        if (seminar.max_score_ > seminar_max_score_) {
            seminar_max_score_ = seminar.max_score_;
        }
    }
};

//реализация метода accept
//Это определение функции-члена класса Lecture, которая принимает объект класса-посетителя
//Visitor по ссылке и вызывает функцию visit() этого посетителя, передавая ей объект Lecture по ссылке
void Lecture::accept(Visitor& v) {
    v.visit(*this);
}

void Lab::accept(Visitor& v) {
    v.visit(*this);
}

void Seminar::accept(Visitor& v) {
    v.visit(*this);
}

// Пример использования
int main() {
    std::vector<Lesson*> lessons = {
        new Lecture(2, 100),
        new Lecture(5, 120),
        new Lab(3, 50),
        new Lab(6, 30),
        new Seminar(1, 75),
        new Seminar(2, 120)
    };
    // Создаем объект предмета
    Subject subject(lessons);

    // Создаем объекты Visitor
    HourCounterVisitor hour_counter;
    ScoreCounterVisitor score_counter;

    subject.accept(hour_counter);// Принимаем Visitor для подсчета количества часов
    subject.accept(score_counter);// Принимаем Visitor для нахождения максимального балла

    std::cout << "Lecture hours: " << hour_counter.total_lecture_hours << "\n";
    std::cout << "Lab hours: " << hour_counter.total_lab_hours << "\n";
    std::cout << "Seminar hours: " << hour_counter.total_seminar_hours << "\n";
    std::cout << "Total hours: " << hour_counter.total_lecture_hours + hour_counter.total_lab_hours + hour_counter.total_seminar_hours << "\n";
    std::cout << "Lecture max score: " << score_counter.lecture_max_score_ << "\n";
    std::cout << "Lab max score: " << score_counter.lab_max_score_ << "\n";
    std::cout << "Seminar max score: " << score_counter.seminar_max_score_ << "\n";
    std::cout << "Total max score: " << score_counter.lecture_max_score_ + score_counter.lab_max_score_ + score_counter.seminar_max_score_ << "\n";

    // Освобождение памяти
    for (auto lesson : lessons) {
        delete lesson;
    }

    return 0;
}