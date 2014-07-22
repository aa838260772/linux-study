#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include <iostream>

class animal
{
    public:
        virtual ~animal() {}
        virtual void display() const = 0;
        virtual animal *copy() const = 0;
};

class cat : public animal
{
    public:
        void display() const
        {
            std::cout << "cat" << std::endl;
        }
        cat *copy() const
        {
            return new cat(*this);
        }
};

class dog : public animal
{
    public:
        void display() const
        {
            std::cout << "dog" << std::endl;
        }
        dog *copy() const
        {
            return new dog(*this);
        }
};

class bear : public animal
{
    public:
        void display() const
        {
            std::cout << "bear" << std::endl;
        }
        bear *copy() const
        {
            return new bear(*this);
        }
};

#endif /*ANIMAL_H*/ 
