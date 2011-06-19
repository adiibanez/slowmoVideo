#ifndef DEFS_SV_HPP
#define DEFS_SV_HPP

#include <QDebug>
#include <QtCore/QString>
#include <QtCore/QSize>
#include <QColor>

enum FlowDirection { FlowDirection_Forward, FlowDirection_Backward };
enum FrameSize { FrameSize_Orig = 1, FrameSize_Small = 2 };

namespace Colours_sV {
    static QColor colOk(158, 245, 94);
    static QColor colBad(247, 122, 48);
}

class Error_sV {
public:
    Error_sV(QString msg);
    QString message() const;
private:
    QString m_message;
};
class FlowBuildingError : public Error_sV {
public: FlowBuildingError(QString msg);
};
class FrameSourceError : public Error_sV {
public: FrameSourceError(QString msg);
};

QString toString(const QSize& size);
QString toString(const FrameSize &size);

//inline QString enumStr(const FrameSize &size) {
//    switch (size) {
//    case FrameSize_Orig:
//        return QString("Orig");
//    case FrameSize_Small:
//        return QString("Small");
//    default:
//        Q_ASSERT(false);
//        return QString("Unknown size");
//    }
//}
inline QString enumStr(const FlowDirection &dir) {
    switch (dir) {
    case FlowDirection_Forward:
        return QString("Forward");
    case FlowDirection_Backward:
        return QString("Backward");
    default:
        Q_ASSERT(false);
        return QString("Unknown direction");
    }
}

inline QDebug operator<<(QDebug qd, const FlowDirection &direction) {
    switch (direction) {
    case FlowDirection_Forward:
        qd << "Forward";
        break;
    case FlowDirection_Backward:
        qd << "Backward";
        break;
    default:
        qd << "Unknown direction";
        Q_ASSERT(false);
        break;
    }
    return qd;
}

inline QDebug operator<<(QDebug qd, const FrameSize &frameSize)
{
    switch(frameSize) {
    case FrameSize_Orig:
        qd << "Original frame size";
        break;
    case FrameSize_Small:
        qd << "Small frame size";
        break;
    default:
        qd << "Unknown frame size";
        Q_ASSERT(false);
        break;
    }
    return qd;
}

#endif // DEFS_SV_HPP
