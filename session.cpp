#include "session.h"
#include "xmlsessionhandler.h"
#include "exceptions.h"


void    Session::ReadFromXml(Session& session, const QString& filename)
{
    XmlSessionHandler xmlhandler(&session);
    QXmlSimpleReader reader;
    reader.setContentHandler(&xmlhandler);

    QFile sessionfile(filename);
    QXmlInputSource source(&sessionfile);
    if (!reader.parse(source))
      throw Exception<EET_PARSEERROR>("invalid session data");
}
