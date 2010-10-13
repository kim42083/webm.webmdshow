#pragma once
//#include "webmmfstream.hpp"

namespace WebmMfSourceLib
{

class WebmMfStreamVideo : public WebmMfStream
{
    WebmMfStreamVideo(
        WebmMfSource*,
        IMFStreamDescriptor*,
        mkvparser::VideoTrack*);

    virtual ~WebmMfStreamVideo();

    WebmMfStreamVideo(const WebmMfStreamVideo&);
    WebmMfStreamVideo& operator=(const WebmMfStreamVideo&);

public:

    static HRESULT CreateStreamDescriptor(
                    mkvparser::Track*,
                    IMFStreamDescriptor*&);

    static HRESULT CreateStream(
                    IMFStreamDescriptor*,
                    WebmMfSource*,
                    mkvparser::Track*,
                    WebmMfStream*&);

    struct SeekInfo
    {
        //mkvparser::Cluster* pCluster;
        const mkvparser::BlockEntry* pBE;
        const mkvparser::CuePoint* pCP;
        const mkvparser::CuePoint::TrackPosition* pTP;
    };

    HRESULT GetCurrMediaTime(LONGLONG&) const;
    void GetSeekInfo(LONGLONG, SeekInfo&) const;

    HRESULT Seek(
        const PROPVARIANT& time,
        const SeekInfo&,
        bool bStart);

protected:

    const mkvparser::BlockEntry* GetCurrBlock() const;
    HRESULT PopulateSample(IMFSample*);

private:

    bool m_bDiscontinuity;
    SeekInfo m_curr;


};

}  //end namespace WebmMfSourceLib
