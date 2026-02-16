#include "tilitapahtumat.h"

tilitapahtumat tilitapahtumat::mapJson(const QJsonObject &json)
{
    tilitapahtumat Tilitapahtumat;
    //Tilitapahtumat.idtili=json["idtili"].toInt();
    Tilitapahtumat.tilinumero=json["tilinumero"].toString();
    Tilitapahtumat.tapahtumat=json["tapahtumat"].toString();
    Tilitapahtumat.summa=json["summa"].toString().toDouble(),'f', 2;
    Tilitapahtumat.ajankohta=json["ajankohta"].toString();
    return Tilitapahtumat;
}
