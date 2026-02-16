#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H
#include <qjsonobject.h>

class tilitapahtumat
{
public:
    int idtili;
    QString tilinumero;
    QString tapahtumat;
    double summa;
    QString ajankohta;
    static tilitapahtumat mapJson(const QJsonObject &json);
};

#endif // TILITAPAHTUMAT_H
