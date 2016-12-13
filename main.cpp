#include <QCoreApplication>
#include "qvector.h"
#include "QDebug"
#include "numeric"
#include "QTime"
#include <random>
double epsilon = 0.3;
double delta = 0.0005;
double teta = 0.0005;
int N = 100;
#define NEURON_NUMBER 15
#define INPUTS_NUMBER 15


void show(QVector<double> vec)
{
    for (int i=0;i<5;i++)
        qDebug()<<vec[3*i]<<vec[3*i+1]<<vec[3*i+2];
    qDebug()<<"";
}

class Neuron
{
public:
    uint inpus_number;
    QVector<double> weights;
public:
    Neuron(int inputs_number = 15);
    Neuron() = default;
    //void learn(QVector<double> input,);
    uint test(QVector<double> input);
    void show_w() {show(weights);}
};

Neuron::Neuron(int inputs_number)
{
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0,10);
    for (int i = 0; i < inputs_number;i++)
        weights.append((double)dist(gen)/10);
}

uint test(QVector<double> input, QVector<Neuron *> neurons)
{
    double inner_product = 0, max = 0;
    uint k = 0;
    for (int i = 0; i < NEURON_NUMBER; i++)
    {
        inner_product = 0;
        for(int j = 0; j < INPUTS_NUMBER; j++)
        {
            inner_product += neurons[i]->weights[j] * input[j];
        }
        //qDebug()<<inner_product;
        if (inner_product > max)
        {
            max = inner_product;
            k = i;
        }
    }
    return k;
}

void learn(QVector<double> input, QVector<Neuron*> neurons)
{
    /*double inner_product = 0, max = 0;
    int k = 0;
    for (int i = 0; i < NEURON_NUMBER; i++)
    {
        inner_product = 0;
        for(int j = 0; j < INPUTS_NUMBER; j++)
        {
            inner_product += neurons[i]->weights[j] * input[j];
        }
        if (inner_product > max)
        {
            max = inner_product;
            k = i;
        }
    }*/
    uint k = test(input,neurons);

    //qDebug()<<k;
    //neurons[k]->show_w();

    for (int i = 0; i < INPUTS_NUMBER; i++)
        neurons[k]->weights[i] += epsilon * (input[i] - neurons[k]->weights[i]);
    //epsilon = epsilon - delta;
    epsilon = epsilon / 1.0005;
    //neurons[k]->show_w();
    //delta = delta - teta;
    //qDebug()<<epsilon<<delta;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<double> one={0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
                two={1,1,1,0,0,1,1,1,1,1,0,0,1,1,1},
                three={1,1,1,0,0,1,1,1,1,0,0,1,1,1,1},
                four={1,0,1,1,0,1,1,1,1,0,0,1,0,0,1},
                five={1,1,1,1,0,0,1,1,1,0,0,1,1,1,1},
                six={1,1,1,1,0,0,1,1,1,1,0,1,1,1,1},
                seven={1,1,1,0,0,1,0,1,0,1,0,0,1,0,0},
                eight={1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
                nine={1,1,1,1,0,1,1,1,1,0,0,1,1,1,1},
                zero={1,1,1,1,0,1,1,0,1,1,0,1,1,1,1};

    QVector<QVector<double>> numbers={zero,one,two,three,four,five,six,seven,eight,nine};

    Neuron *new_neuron;
    QVector<Neuron *> neurons;

    for (int i=0;i<NEURON_NUMBER;i++)
    {
        new_neuron = new Neuron(INPUTS_NUMBER);
        neurons.append(new_neuron);
        qDebug()<<i;
        neurons[i]->show_w();
    }

    int current;
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0,9); // distribute results between 1 and 6 inclusive.
    for (int i = 0; i < N; i++)
    {
        //srand((uint)QTime::currentTime().msec());
        //current =rand()%10;
        current = dist(gen);
        //qDebug()<<current;
        learn(numbers[current],neurons);
    }

    int k = 0;
    //qDebug()<<test(numbers[0],neurons);
    //neurons[1]->show_w();

    qDebug()<<epsilon;
    for (int i = 0; i < 10; i++)
    {
        k = test(numbers[i],neurons);
        qDebug()<<"\n"<<i<<k<<"\n";
        neurons[k]->show_w();
    }


    return a.exec();
}
