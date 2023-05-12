#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "D:\PatternVisitor\6_2\6_2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LessonTests
{

    // Test for Lecture
    TEST_CLASS(TestsForLecture)
    {
    public:
        //���� ��� ������������ ������ ������
        TEST_METHOD(LectureConstructorTestsSetsHoursAndMaxScore)
        {
            int hours = 3;
            int max_score = 100;

            Lecture lecture(hours, max_score);

            Assert::AreEqual(hours, lecture.hours_);
            lectures.push_back(new Lecture(2, 100));
            lectures.push_back(new Lecture(6, 200));
            lectures.push_back(new Lecture(12, 110));
            lectures.push_back(new Lecture(10, 30));
            lectures.push_back(new Lecture(8, 220));
            Subject subject(lectures);

            // �������� ����� accept � ������� Subject � ��������� ��� ������� HourCounterVisitor
            subject.accept(visitor);

            // ���������, ��� ����� ���������� ����� ��� ���� ����� "������" ���� ��������� �����
            Assert::AreEqual(38, visitor.total_lecture_hours);
        }

        TEST_METHOD(TestScoreCounterVisitorLecture)
        {
            // ������� ������ ScoreCounterVisitor
            ScoreCounterVisitor visitor;

            // ������� ����� ������� "Lectures"
            std::vector<Lesson*> lectures;
            lectures.push_back(new Lecture(2, 100));
            lectures.push_back(new Lecture(6, 200));
            Subject subject(lectures);

            // �������� ����� accept � ������� Subject � ��������� ��� ������� ScoreCounterVisitor
            subject.accept(visitor);

            // ���������, ��� ������������ ���������� ������ ��� ���� ����� "Lectures" ���� ��������� �����
            Assert::AreEqual(200, visitor.lecture_max_score_);
        }

        TEST_METHOD(TestLectureAccept)
        {
            Lecture lecture(10, 100);
            HourCounterVisitor visitor;
            lecture.accept(visitor);

            Assert::AreEqual(visitor.total_lecture_hours, 10);
            Assert::AreEqual(visitor.total_lab_hours, 0);
            Assert::AreEqual(visitor.total_seminar_hours, 0);
        }
    };

    // Test for Lab
    TEST_CLASS(TestsForLab)
    {
    public:
        TEST_METHOD(LabConstructorTestsSetsHoursAndMaxScore)
        {
            int hours = 2;
            int max_score = 50;

            Lab lab(hours, max_score);

            Assert::AreEqual(hours, lab.hours_);
            Assert::AreEqual(max_score, lab.max_score_);
        }

        TEST_METHOD(TestHourCounterVisitorforLab)
        {
            // ������� ������ HourCounterVisitor
            HourCounterVisitor visitor;

            // ������� ����� ������� "������������ ������"
            std::vector<Lesson*> labs;
            labs.push_back(new Lab(3, 50));
            labs.push_back(new Lab(4, 100));
            labs.push_back(new Lab(2, 110));
            Subject subject(labs);

            // �������� ����� accept � ������� Subject � ��������� ��� ������� HourCounterVisitor
            subject.accept(visitor);

            // ���������, ��� ����� ���������� ����� ��� ���� ����� "������������ ������" ���� ��������� �����
            Assert::AreEqual(9, visitor.total_lab_hours);
        }

        TEST_METHOD(TestScoreCounterVisitorLab)
        {
            // ������� ������ ScoreCounterVisitor
            ScoreCounterVisitor visitor;

            // ������� ����� ������� "Lab"
            std::vector<Lesson*> lab;
            lab.push_back(new Lab(5, 150));
            lab.push_back(new Lab(3, 50));
            lab.push_back(new Lab(4, 100));
            Subject subject(lab);

            // �������� ����� accept � ������� Subject � ��������� ��� ������� ScoreCounterVisitor
            subject.accept(visitor);

            // ���������, ��� ������������ ���������� ������ ��� ���� ����� "Lab" ���� ��������� �����

            Assert::AreEqual(150, visitor.lab_max_score_);
        }

        TEST_METHOD(TestLabAccept)
        {
            Lab lab(5, 50);
            HourCounterVisitor visitor;
            lab.accept(visitor);

            Assert::AreEqual(visitor.total_lecture_hours, 0);
            Assert::AreEqual(visitor.total_lab_hours, 5);
            Assert::AreEqual(visitor.total_seminar_hours, 0);
        }
    };

    // Test constructor for Seminar
    TEST_CLASS(TestsForSeminar)
    {
    public:
        TEST_METHOD(SeminarConstructorTestsSetsHoursAndMaxScore)
        {

            int hours = 1;
            int max_score = 25;

            Seminar seminar(hours, max_score);

            Assert::AreEqual(hours, seminar.hours_);
            Assert::AreEqual(max_score, seminar.max_score_);
        }

        TEST_METHOD(TestHourCounterVisitorforSeminar)
        {
            // ������� ������ HourCounterVisitor
            HourCounterVisitor visitor;

            // ������� ����� ������� "�������"
            std::vector<Lesson*> seminars;
            seminars.push_back(new Seminar(1, 75));
            seminars.push_back(new Seminar(2, 100));
            seminars.push_back(new Seminar(5, 120));
            Subject subject(seminars);

            // �������� ����� accept � ������� Subject � ��������� ��� ������� HourCounterVisitor
            subject.accept(visitor);

            // ���������, ��� ����� ���������� ����� ��� ���� ����� "�������" ���� ��������� �����
            Assert::AreEqual(8, visitor.total_seminar_hours);
        }

        TEST_METHOD(TestScoreCounterVisitorSeminar)
        {
            // ������� ������ ScoreCounterVisitor
            ScoreCounterVisitor visitor;

            // ������� ����� ������� "Seminar"
            std::vector<Lesson*> lessons;
            lessons.push_back(new Seminar(1, 75));
            lessons.push_back(new Seminar(2, 100));
            Subject subject(lessons);

            // �������� ����� accept � ������� Subject � ��������� ��� ������� ScoreCounterVisitor
            subject.accept(visitor);

            // ���������, ��� ������������ ���������� ������ ��� ���� ����� "Seminar" ���� ��������� �����

            Assert::AreEqual(100, visitor.seminar_max_score_);
        }

        TEST_METHOD(TestSeminarAccept)
        {
            Seminar seminar(2, 20);
            HourCounterVisitor visitor;
            seminar.accept(visitor);

            Assert::AreEqual(visitor.total_lecture_hours, 0);
            Assert::AreEqual(visitor.total_lab_hours, 0);
            Assert::AreEqual(visitor.total_seminar_hours, 2);
        }

    };

    TEST_CLASS(TestsForAllTypes)
    {
    public:
        //����� ���������� ����� ��� ������� ����
        TEST_METHOD(TestHourCounterVisitorForAllTypes)
        {
            // ������� ������ HourCounterVisitor
            HourCounterVisitor visitor;

            // ������� ����� �������
            std::vector<Lesson*> lessons;
            lessons.push_back(new Lecture(2, 100));
            lessons.push_back(new Lecture(3, 150));
            lessons.push_back(new Lecture(12, 120));
            lessons.push_back(new Lab(3, 50));
            lessons.push_back(new Seminar(1, 75));
            lessons.push_back(new Seminar(2, 185));
            Subject subject(lessons);

            // �������� ����� accept � ������� Subject � ��������� ��� ������� HourCounterVisitor
            subject.accept(visitor);

            // ���������, ��� ����� ���������� ����� ��� ������� ���� ����� ���� ��������� �����
            Assert::AreEqual(17, visitor.total_lecture_hours);
            Assert::AreEqual(3, visitor.total_lab_hours);
            Assert::AreEqual(3, visitor.total_seminar_hours);
        }
        //����� ���������� ������ ��� ������� ����
        TEST_METHOD(TestScoreCounterVisitorForAllTypes)
        {
            // ������� ������ ScoreCounterVisitor
            ScoreCounterVisitor visitor;

            // ������� ����� �������
            std::vector<Lesson*> lessons;
            lessons.push_back(new Lecture(2, 100));
            lessons.push_back(new Lecture(6, 200));
            lessons.push_back(new Lab(3, 50));
            lessons.push_back(new Lab(4, 100));
            lessons.push_back(new Seminar(1, 75));
            lessons.push_back(new Seminar(2, 100));
            Subject subject(lessons);

            // �������� ����� accept � ������� Subject � ��������� ��� ������� ScoreCounterVisitor
            subject.accept(visitor);

            // ���������, ��� ������������ ���������� ������ ��� ������� ���� ����� ���� ��������� �����
            Assert::AreEqual(200, visitor.lecture_max_score_);
            Assert::AreEqual(100, visitor.lab_max_score_);
            Assert::AreEqual(100, visitor.seminar_max_score_);
        }
        //��� ��� ������, � ���-�� ������ � ���-�� �����
        TEST_METHOD(TestSubjectAccept)
        {
            std::vector<Lesson*> lessons;
            lessons.push_back(new Lecture(10, 100));
            lessons.push_back(new Lecture(20, 150));
            lessons.push_back(new Lab(5, 50));
            lessons.push_back(new Seminar(2, 20));
            lessons.push_back(new Seminar(3, 18));

            Subject subject(lessons);
            HourCounterVisitor hour_visitor;
            ScoreCounterVisitor score_visitor;

            subject.accept(hour_visitor);
            subject.accept(score_visitor);

            Assert::AreEqual(hour_visitor.total_lecture_hours, 30);
            Assert::AreEqual(hour_visitor.total_lab_hours, 5);
            Assert::AreEqual(hour_visitor.total_seminar_hours, 5);

            Assert::AreEqual(score_visitor.lecture_max_score_, 150);
            Assert::AreEqual(score_visitor.lab_max_score_, 50);
            Assert::AreEqual(score_visitor.seminar_max_score_, 20);

            for (auto lesson : lessons) {
                delete lesson;
            }
        }
        //����������� ���� ����, ��� ������ ������ ������
        TEST_METHOD(TestHourCounterVisitor)
        {
            std::vector<Lesson*> lessons = { new Lecture(2, 100), new Lab(3, 90), new Seminar(1, 80), new Lecture(3, 100), new Seminar(10, 80) };
            Subject subject(lessons);
            HourCounterVisitor visitor;
            subject.accept(visitor);

            Assert::AreEqual(5, visitor.total_lecture_hours);
            Assert::AreEqual(3, visitor.total_lab_hours);
            Assert::AreEqual(11, visitor.total_seminar_hours);
        }
        //����������� ���� ����, ��� ������ ������ ������
        TEST_METHOD(TestScoreCounterVisitor)
        {
            std::vector<Lesson*> lessons = { new Lecture(2, 100), new Lab(3, 90), new Seminar(1, 80) };
            Subject subject(lessons);
            ScoreCounterVisitor visitor;
            subject.accept(visitor);

            Assert::AreEqual(100, visitor.lecture_max_score_);
            Assert::AreEqual(90, visitor.lab_max_score_);
            Assert::AreEqual(80, visitor.seminar_max_score_);
        }

        TEST_METHOD(TestHourCounterVisitorEmptySubject)
        {
            std::vector<Lesson*> lessons;
            Subject subject(lessons);
            HourCounterVisitor visitor;
            subject.accept(visitor);

            Assert::AreEqual(0, visitor.total_lecture_hours);
            Assert::AreEqual(0, visitor.total_lab_hours);
            Assert::AreEqual(0, visitor.total_seminar_hours);
        }

        TEST_METHOD(TestScoreCounterVisitorEmptySubject)
        {
            std::vector<Lesson*> lessons;
            Subject subject(lessons);
            ScoreCounterVisitor visitor;
            subject.accept(visitor);

            Assert::AreEqual(0, visitor.lecture_max_score_);
            Assert::AreEqual(0, visitor.lab_max_score_);
            Assert::AreEqual(0, visitor.seminar_max_score_);
        }

    };
}
