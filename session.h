#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <vector>
#include <QSizeF>
#include <tuple>
#include <map>
#include <QRectF>
#include <algorithm>

#include <stdexcept>

class Thread;
class Window;

class Session
{
public:
    typedef std::map<QString, QString> attributes_t;

    Session() {}

    QString backgroundImagePath() const { return _backgroundImagePath; }
    void setBackgroundImagePath(const QString& path) { _backgroundImagePath = path; }

    QSizeF resolution() const { return _resolution; }
    void setResolution(const QSizeF& resolution) { _resolution = resolution; }

    void addThread() { _threads.push_back(thread_t()); }
    void addWindow(const QString& name,
                   const QRectF& geometry,
                   double zorder, bool hasBorder)
    {
        _windows.push_back(std::make_pair(std::make_tuple(name,geometry,zorder,hasBorder),
                                          std::vector<content_t>()));
    }
    void addContent(const QString& name, const QString& type, const QString& url )
    {
        Q_ASSERT(!_windows.empty());
        _windows.back().second.push_back(std::make_tuple(name,type,url));
    }

    void addEvent(const QString& member, const attributes_t& attrs)
    {
        Q_ASSERT(!_threads.empty());
        _threads.back().push_back(std::make_pair(member, attrs));
    }

    QString windowId(size_t index) const { return std::get<0>(_windows[index].first); }
    QRectF  windowRect(size_t index) const { return std::get<1>(_windows[index].first); }
    double  windowZLevel(size_t index) const { return std::get<2>(_windows[index].first); }
    bool    windowHasBorder(size_t index) const { return std::get<3>(_windows[index].first); }
//    QRectF  windowRect(size_t index) const { return std::get<1>(_windows[index].first); }

    size_t countOfWindows() const { return _windows.size(); }
    size_t countOfThreads() const { return _threads.size(); }
    size_t countOfContents(size_t windex) const { return _windows[windex].second.size(); }

    QString contentId(size_t windex, size_t cindex) const
        { return std::get<0>(_windows[windex].second[cindex]); }
    QString contentType(size_t windex, size_t cindex) const
        { return std::get<1>(_windows[windex].second[cindex]); }
    QString contentUrl(size_t windex, size_t cindex) const
        { return std::get<2>(_windows[windex].second[cindex]); }

    size_t countOfEvents(size_t tindex) const { return _threads[tindex].size(); }

    QString eventAttribute(const QString& key, size_t tindex, size_t eindex) const
    {
        const attributes_t& attrs = _threads[tindex][eindex].second;
        try {
            QString value = attrs.at(key);
            return value;
        } catch(std::out_of_range&) {
            return QString::null;
        }
    }

    //c hack
    QString firstEventAttribute(size_t tindex, size_t eindex) const
    {
        return _threads[tindex][eindex].second.begin()->second;
    }

    QString eventName(size_t tindex, size_t eindex) const { return _threads[tindex][eindex].first; }


    static void ReadFromXml(Session& session, const QString& filename);

private:
typedef std::tuple<QString/*name*/, QString/*type*/, QString/*url*/> content_t;
typedef std::vector< std::pair<QString, attributes_t> > thread_t;
typedef std::tuple<QString, QRectF, double/*Z*/, bool /*border*/> window_t;
typedef std::pair< window_t, std::vector< content_t > > windowdata_t;

    QSizeF  _resolution;
    QString _backgroundImagePath;

    std::vector<thread_t> _threads;

    std::vector<windowdata_t> _windows;

};

#endif //SESSION_H
