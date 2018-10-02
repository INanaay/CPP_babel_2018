//
// Created by NANAA on 01/10/18.
//

#ifndef CPP_BABEL_2018_READSERVERWORKER_HPP
#define CPP_BABEL_2018_READSERVERWORKER_HPP

#include <QtCore/QThread>
#include <iostream>

class readServerWorker : public QThread
{
Q_OBJECT
void run() override;
};

#endif //CPP_BABEL_2018_READSERVERWORKER_HPP
