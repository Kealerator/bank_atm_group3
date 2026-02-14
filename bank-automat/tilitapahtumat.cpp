#include "tilitapahtumat.h"

tilitapahtumat tilitapahtumat::mapJson(const QJsonObject &json)
{
    tilitapahtumat Tilitapahtumat;
    Tilitapahtumat.idtili=json["idtili"].toInt();
    Tilitapahtumat.tilinumero=json["Tilinumero"].toString();
    Tilitapahtumat.tapahtumat=json["tapahtumat"].toString();
    Tilitapahtumat.summa=json["summa"].toInt();
    Tilitapahtumat.ajankohta=json["ajankohta"].toString();
    return Tilitapahtumat;
}
