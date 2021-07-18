//
//  VIPKIDRtcEngine SDK
//
//  Copyright (c) 2019 VIPKID.io. All rights reserved.
//

/**
 @defgroup createVIPKIDRtcEngine Create an VIPKIDRtcEngineInterface
 */

#ifndef VIPKID_RTC_ENGINE_INTERFACE_H
#define VIPKID_RTC_ENGINE_INTERFACE_H
#include <stdio.h>
#include <stdint.h>
namespace VIPKID {
#define   VK_ENGINE_VERSION "1.0.0.10"
#define   VK_MAX_LENGTH   512
/**
 * Video dimensions.
 */
struct VideoDimensions {
    /** Width (pixels) of the video. */
    int width;
      /** Height (pixels) of the video. */
    int height;
    VideoDimensions()
        : width(320), height(240)
    {}
    VideoDimensions(int w, int h)
        : width(w), height(h)
    {}
};
/** Video frame rates. */
enum FRAME_RATE
{
      /** 1: 1 fps */
    FRAME_RATE_FPS_1 = 1,
        /** 7: 7 fps */
    FRAME_RATE_FPS_7 = 7,
      /** 10: 10 fps */
    FRAME_RATE_FPS_10 = 10,
    /** 15: 15 fps */
    FRAME_RATE_FPS_15 = 15,
        /** 24: 24 fps */
    FRAME_RATE_FPS_24 = 24,
    /** 30: 30 fps */
    FRAME_RATE_FPS_30 = 30,
    /** 60: 60 fps (Windows and macOS only) */
    FRAME_RATE_FPS_60 = 60,
};
/** Video encoder configurations.
 */
struct VideoEncoderConfiguration {
  /** The video frame dimensions (px) used to specify the video quality and measured by the total number of pixels along a frame's width and height: VideoDimensions. The default value is 640 x 360.
  */
    VideoDimensions dimensions;
    /** The frame rate of the video: #FRAME_RATE. The default value is 15.

     Note that we do not recommend setting this to a value greater than 30.
    */
    FRAME_RATE frameRate;
    /**
       encode bitrate,if set to 0 vendor should selfadaptive birtate or use the assign birtrate
     */
    int      videoBitrate;
};
/** Local video state types
 */
enum VK_LOCAL_VIDEO_STREAM_STATE
{
    /** Initial state */
    VK_LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,
    /** The capturer starts successfully. */
    VK_LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1,
    /** The first video frame is successfully encoded. */
    VK_LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,
    /** The local video fails to start. */
    VK_LOCAL_VIDEO_STREAM_STATE_FAILED = 3
};

/** Local video state error codes
 */
enum VK_LOCAL_VIDEO_STREAM_ERROR {
    /** The local video is normal. */
    VK_LOCAL_VIDEO_STREAM_ERROR_OK = 0,
    /** No specified reason for the local video failure. */
    VK_LOCAL_VIDEO_STREAM_ERROR_FAILURE = 1,
    /** No permission to use the local video device. */
    VK_LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
    /** The local video capturer is in use. */
    VK_LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY = 3,
    /** The local video capture fails. Check whether the capturer is working properly. */
    VK_LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = 4,
    /** The local video encoding fails. */
    VK_LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5,
    /** No camera device. */
    VK_LOCAL_VIDEO_STREAM_ERROR_DEVICE_NOT_FOUND = 6
};

/** Local audio state types.
 */
enum VK_LOCAL_AUDIO_STREAM_STATE
{
    /** 0: The local audio is in the initial state.
     */
    VK_LOCAL_AUDIO_STREAM_STATE_STOPPED = 0,
    /** 1: The recording device starts successfully.
     */
    VK_LOCAL_AUDIO_STREAM_STATE_RECORDING = 1,
    /** 2: The first audio frame encodes successfully.
     */
    VK_LOCAL_AUDIO_STREAM_STATE_ENCODING = 2,
    /** 3: The local audio fails to start.
     */
    VK_LOCAL_AUDIO_STREAM_STATE_FAILED = 3
};

/** Local audio state error codes.
 */
enum VK_LOCAL_AUDIO_STREAM_ERROR
{
    /** 0: The local audio is normal.
     */
    VK_LOCAL_AUDIO_STREAM_ERROR_OK = 0,
    /** 1: No specified reason for the local audio failure.
     */
    VK_LOCAL_AUDIO_STREAM_ERROR_FAILURE = 1,
    /** 2: No permission to use the local audio device.
     */
    VK_LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
    /** 3: The microphone is in use.
     */
    VK_LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY = 3,
    /** 4: The local audio recording fails. Check whether the recording device
     * is working properly.
     */
    VK_LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE = 4,
    /** 5: The local audio encoding fails.
     */
    VK_LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 5,
    /** 6: No recording audio device.
    */
    VK_LOCAL_AUDIO_STREAM_ERROR_NO_RECORDING_DEVICE = 6,
    /** 7: No playout audio device.
    */
    VK_LOCAL_AUDIO_STREAM_ERROR_NO_PLAYOUT_DEVICE = 7
};

/** Remote audio states.
 */
enum VK_REMOTE_AUDIO_STATE
{
      /** 0: The remote audio is in the default state, probably due to
       * #REMOTE_AUDIO_REASON_LOCAL_MUTED (3),
       * #REMOTE_AUDIO_REASON_REMOTE_MUTED (5), or
       * #REMOTE_AUDIO_REASON_REMOTE_OFFLINE (7).
       */
    VK_REMOTE_AUDIO_STATE_STOPPED = 0,  // Default state, audio is started or remote user disabled/muted audio stream
      /** 1: The first remote audio packet is received.
       */
    VK_REMOTE_AUDIO_STATE_STARTING = 1,  // The first audio frame packet has been received
      /** 2: The remote audio stream is decoded and plays normally, probably
       * due to #REMOTE_AUDIO_REASON_NETWORK_RECOVERY (2),
       * #REMOTE_AUDIO_REASON_LOCAL_UNMUTED (4), or
       * #REMOTE_AUDIO_REASON_REMOTE_UNMUTED (6).
       */
    VK_REMOTE_AUDIO_STATE_DECODING = 2,  // The first remote audio frame has been decoded or fronzen state ends
      /** 3: The remote audio is frozen, probably due to
       * #REMOTE_AUDIO_REASON_NETWORK_CONGESTION (1).
       */
    VK_REMOTE_AUDIO_STATE_FROZEN = 3,    // Remote audio is frozen, probably due to network issue
      /** 4: The remote audio fails to start, probably due to
       * #REMOTE_AUDIO_REASON_INTERNAL (0).
       */
    VK_REMOTE_AUDIO_STATE_FAILED = 4,    // Remote audio play failed
};

/** Remote audio state reasons.
 */
enum VK_REMOTE_AUDIO_STATE_REASON
{
      /** 0: Internal reasons.
       */
    VK_REMOTE_AUDIO_REASON_INTERNAL = 0,
      /** 1: Network congestion.
       */
    VK_REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 1,
      /** 2: Network recovery.
       */
    VK_REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 2,
      /** 3: The local user stops receiving the remote audio stream or
       * disables the audio module.
       */
    VK_REMOTE_AUDIO_REASON_LOCAL_MUTED = 3,
      /** 4: The local user resumes receiving the remote audio stream or
       * enables the audio module.
       */
    VK_REMOTE_AUDIO_REASON_LOCAL_UNMUTED = 4,
      /** 5: The remote user stops sending the audio stream or disables the
       * audio module.
       */
    VK_REMOTE_AUDIO_REASON_REMOTE_MUTED = 5,
      /** 6: The remote user resumes sending the audio stream or enables the
       * audio module.
       */
    VK_REMOTE_AUDIO_REASON_REMOTE_UNMUTED = 6,
      /** 7: The remote user leaves the channel.
       */
    VK_REMOTE_AUDIO_REASON_REMOTE_OFFLINE = 7,
};

/** The state of the remote video. */
enum VK_REMOTE_VIDEO_STATE {
    /** 0: The remote video is in the default state, probably due to #REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED (3), #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5), or #REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE (7).
     */
    VK_REMOTE_VIDEO_STATE_STOPPED = 0,

    /** 1: The first remote video packet is received.
     */
    VK_REMOTE_VIDEO_STATE_STARTING = 1,

    /** 2: The remote video stream is decoded and plays normally, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY (2), #REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED (4), #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6), or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY (9).
     */
    VK_REMOTE_VIDEO_STATE_DECODING = 2,

    /** 3: The remote video is frozen, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION (1) or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK (8).
     */
    VK_REMOTE_VIDEO_STATE_FROZEN = 3,

    /** 4: The remote video fails to start, probably due to #REMOTE_VIDEO_STATE_REASON_INTERNAL (0).
     */
    VK_REMOTE_VIDEO_STATE_FAILED = 4
};

/** The reason of the remote video state change. */
enum VK_REMOTE_VIDEO_STATE_REASON {
    /** 0: Internal reasons.
     */
    VK_REMOTE_VIDEO_STATE_REASON_INTERNAL = 0,

    /** 1: Network congestion.
     */
    VK_REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = 1,

    /** 2: Network recovery.
     */
    VK_REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = 2,

    /** 3: The local user stops receiving the remote video stream or disables the video module.
     */
    VK_REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = 3,

    /** 4: The local user resumes receiving the remote video stream or enables the video module.
     */
    VK_REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = 4,

    /** 5: The remote user stops sending the video stream or disables the video module.
     */
    VK_REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = 5,

    /** 6: The remote user resumes sending the video stream or enables the video module.
     */
    VK_REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = 6,

    /** 7: The remote user leaves the channel.
     */
    VK_REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = 7,

    /** 8: The remote media stream falls back to the audio-only stream due to poor network conditions.
     */
    VK_REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = 8,

    /** 9: The remote media stream switches back to the video stream after the network conditions improve.
     */
    VK_REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = 9

};

/** Statistics of the channel.
 */
struct RtcStats
{

    /**
     Total number of bytes transmitted, represented by an aggregate value.
     */
    unsigned int txBytes;
    /**
     Total number of bytes received, represented by an aggregate value.
     */
    unsigned int rxBytes;
     /** Total number of audio bytes sent (bytes), represented
     * by an aggregate value.
     */
    unsigned int txAudioBytes;
    /** Total number of video bytes sent (bytes), represented
     * by an aggregate value.
     */
    unsigned int txVideoBytes;
    /** Total number of audio bytes received (bytes) before
     * network countermeasures, represented by an aggregate value.
     */
    unsigned int rxAudioBytes;
    /** Total number of video bytes received (bytes),
     * represented by an aggregate value.
     */
    unsigned int rxVideoBytes;

    /**
     Transmission bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short txKBitRate;
    /**
     Receive bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short rxKBitRate;
    /**
     Audio receive bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short rxAudioKBitRate;
    /**
     Audio transmission bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short txAudioKBitRate;
    /**
     Video receive bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short rxVideoKBitRate;
    /**
     Video transmission bitrate (Kbps), represented by an instantaneous value.
     */
    unsigned short txVideoKBitRate; 
    /**
     Application CPU usage (%).
     */
    double cpuAppUsage;
    /**
     System CPU usage (%).
     */
    double cpuTotalUsage;
    /**  client to server rtt
     */
    int rtt;
    /**
     Application memory usage (%).
     */
    double memoryAppUsageRatio;
    /**
     System memory usage (%).
     */
    double memoryTotalUsageRatio;
    /**
     Application memory size (KB).
     */
    int memoryAppUsageInKbytes;

  RtcStats()
        :txBytes(0)
      , rxBytes(0)
      , txAudioBytes(0)
      , txVideoBytes(0)
      , rxAudioBytes(0)
      , rxVideoBytes(0)
      , txKBitRate(0)
      , rxKBitRate(0)
      , rxAudioKBitRate(0)
      , txAudioKBitRate(0)
      , rxVideoKBitRate(0)
      , txVideoKBitRate(0)
      , rtt(0)
      , cpuAppUsage(0)
      , cpuTotalUsage(0)
      , memoryAppUsageRatio(0)
      , memoryTotalUsageRatio(0)
      , memoryAppUsageInKbytes(0) {}
};
struct ChannelMediaOptions {
    bool autoSubscribeAudio;
    bool autoSubscribeVideo;
    ChannelMediaOptions()
    : autoSubscribeAudio(true)
    , autoSubscribeVideo(true)
    {}
};
enum REMOTE_VIDEO_STREAM_TYPE
{
    VIDEO_STREAM_HIGH = 0,
    VIDEO_STREAM_LOW = 1,
};
typedef REMOTE_VIDEO_STREAM_TYPE  LOCAL_VIDEO_STREAM_TYPE;
enum VIDEO_FRAME_TYPE {
    FRAME_TYPE_YUV420P_ONE  = 0,  //YUV 420p format,ONE buffer
    FRAME_TYPE_YUV420P =1,   //YUV 420P format,three buffer
    FRAME_TYPE_RGBA = 2,    // RGBA format
};
enum VIDEO_OBSERVER_POSITION {
    POSITION_POST_CAPTURER = 1 << 0,
    POSITION_PRE_RENDERER = 1 << 1,
    POSITION_PRE_ENCODER = 1 << 2,
};

struct VideoFrame {
    VIDEO_FRAME_TYPE type; // only support FRAME_TYPE_YUV420P_ONE and FRAME_TYPE_YUV420P
    int width;  //width of video frame
    int height;  //height of video frame
    int yStride;  //stride of Y data buffer
    int uStride;  //stride of U data buffer
    int vStride;  //stride of V data buffer
    void* yBuffer;  //Y data buffer,if format is FRAME_TYPE_YUV420P_ONE ,datas save here
    void* uBuffer;  //U data buffer
    void* vBuffer;  //V data buffer
    int rotation; // rotation of this frame (0, 90, 180, 270)
    int streamType; // 0 :camera, 2:screen
    int dataSize;   // buffer size, if format is FRAME_TYPE_YUV420P_ONE ,must set
};
enum AUDIO_FRAME_TYPE {
    FRAME_TYPE_PCM16 = 0,  //PCM 16bit little endian
};
enum VKWorkMode {
  UNICAST,    // 1v1，require low latency
  BROADCAST,  // one class may have many audiances
  SMALLCLASS, // one class has six student so far
  SUPERSMALLCLASS, // one class is separated into some small rooms
  KB,             // recorded broadcast
  VKROOM          // reserved
};
enum VKUserRole {
    ANCHOR=1,     // BRAODCASTER
    AUDIENCE,
    ASSISTENT,  
};
struct AudioFrame {
    AUDIO_FRAME_TYPE type;
    int samples;  //number of samples in this frame
    int bytesPerSample;  //number of bytes per sample: 2 for PCM16
    int channels;  //number of channels (data are interleaved if stereo)
    int samplesPerSec;  //sampling rate
    int volume;    // [0-2550] if volume greater then 0,use this volume
    void* buffer;  //data buffer
};
enum VK_ERROR {
    ERROR_VENDOR_DEFINE = 1000, // VENDOR DIFINE FATAL ERROR
    ERROR_EXPIRED_TOKEN ,   // TOKEN ERROR
    VIDEO_DEVICE_IN_USE ,   // VIDEO DEVICE BUSY
    AUDIO_DEVICE_IN_USE ,   // AUDIO DEVICE BUSY
    ERROR_PLAYBACK_DEVICE,   // PLAY BACK DEVICE ERROR
    ERROR_SERVER_INTERNAL,
    
    
};

class ISubChannel;
class ISubChannelEventHandler
{
public:
    
    virtual void onSubChannelError(ISubChannel *rtcChannel, int err, const char* msg) =0;
    
    virtual void onJoinSubChannelSuccess(ISubChannel *rtcChannel, const char* userId, int elapsed)=0;
    
    virtual void onLeaveSubChannel(ISubChannel *rtcChannel) =0;
  
    virtual void onUserJoined(ISubChannel *rtcChannel, const char* userId, int elapsed) =0;
    
    virtual void onUserOffline(ISubChannel *rtcChannel, const char* userId) = 0;
    
};

class ISubChannel
{
public:
    virtual int release() = 0;
    
    virtual int setSubChannelEventHandler(ISubChannelEventHandler *channelEh) = 0;

    virtual int joinChannel(const char* token,
                            const char* info,
                            const char* userId,
                            const ChannelMediaOptions& options) = 0;

    
    virtual int leaveChannel() = 0;
    
    /** Allows this connection to upload stream. This method will unpublish the current publishing connection if there exists.
     */
    virtual int publish() = 0;
    
    /** Stops publishing stream.
     */
    virtual int unpublish() = 0;
    
    /** Gets the channel ID of IChannel.
     
     @return Channel ID of IChannel.
     */
    virtual const char *channelId() = 0;
    
    
    virtual int muteAllRemoteAudioStreams(bool mute) = 0;
    
    virtual int muteRemoteAudioStream(const char* userId, bool mute) = 0;
    
    virtual int muteAllRemoteVideoStreams(bool mute) = 0;
    
    virtual int muteRemoteVideoStream(const char* userId, bool mute) = 0;
       
};

/** The SDK uses the IRtcEngineEventHandler interface class to send callbacks to the application. The application inherits the methods of this interface class to retrieve these callbacks.

 All methods in this interface class have default (empty) implementations. Therefore, the application can only inherit some required events. In the callbacks, avoid time-consuming tasks or calling blocking APIs, such as the SendMessage method. Otherwise, the SDK may not work properly.
 */
class IVKRtcEngineHandler
{
public:
   
    /** Reports an error during SDK runtime.

     In most cases, the SDK cannot fix the issue and resume running. The SDK requires the application to take action or informs the user about the issue.

     For example, the SDK reports an #ERR_START_CALL error when failing to initialize a call. The application informs the user that the call initialization failed and invokes the \ref IRtcEngine::leaveChannel "leaveChannel" method to leave the channel.

     @param errCode Error code: #VK_ERROR.
     @param msg Pointer to the error message.
     */
    virtual void onError(int errCode, const char* msg) =0;
    /** Reports the core log during SDK runtime..
     @param tag diff with other module.
     @param msg log info.
     */
    virtual void onLogInfo(const char* tag, const char* msg) = 0;

    /** Occurs when a user joins a specified channel.

     This callback notifies the application that a user joins a specified channel when the application calls the \ref IRtcEngine::joinChannel "joinChannel" method.

     @param  elapsed Time elapsed (ms) from the user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
     */
    virtual void onJoinChannelSuccess(int32_t elapsed) =0;


    /** Occurs when a user leaves the channel.

    This callback notifies the application that a user leaves the channel when the application calls the \ref IRtcEngine::leaveChannel "leaveChannel" method.

    The application retrieves information

     @param reason 0：normal exitRoom ；1：kick off by server；2：room is none.
     */
    virtual void onLeaveChannel(int32_t reason)  =0;

    /** Occurs when a user or host joins the channel.

     - Communication profile: This callback notifies the application that another user joins the channel. If other users are already in the channel, the SDK also reports to the application on the existing users.
     - Live-broadcast profile: This callback notifies the application that the host joins the channel. If other hosts are already in the channel, the SDK also reports to the application on the existing hosts. We recommend limiting the number of hosts to 17.

     The SDK triggers this callback under one of the following circumstances:
     - A remote user/host joins the channel by calling the \ref VIPKID::rtc::IRtcEngine::joinChannel "joinChannel" method.
     - A remote user switches the user role to the host by calling the \ref VIPKID::rtc::IRtcEngine::setClientRole "setClientRole" method after joining the channel.
     - A remote user/host rejoins the channel after a network interruption.
     - The host injects an online media stream into the channel by calling the \ref VIPKID::rtc::IRtcEngine::addInjectStreamUrl "addInjectStreamUrl" method.

     @note In the Live-broadcast profile:
     - The host receives this callback when another host joins the channel.
     - The audience in the channel receives this callback when a new host joins the channel.
     - When a web application joins the channel, the SDK triggers this callback as long as the web application publishes streams.

     @param userId User ID of the user or host joining the channel.
     @param elapsed Time delay (ms) from the local user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
     */
    virtual void onUserJoined(const char* userId, int elapsed) = 0;

    /** Occurs when a remote user (Communication)/host (Live Broadcast) leaves the channel.

    Reasons why the user is offline:

    - Leave the channel: When the user/host leaves the channel, the user/host sends a goodbye message. When the message is received, the SDK assumes that the user/host leaves the channel.
    - Drop offline: When no data packet of the user or host is received for a certain period of time (20 seconds for the Communication profile, and more for the Live-broadcast profile), the SDK assumes that the user/host drops offline. Unreliable network connections may lead to false detections, so we recommend using a signaling system for more reliable offline detection.

     @param userId User ID of the user leaving the channel or going offline.
     @param reason Reason why the user is offline: #USER_OFFLINE_REASON_TYPE.
     */
    virtual void onUserOffline(const char* userId, int32_t reason) =0;


    /** Reports the statistics of the current call session once every two
     * seconds.
     *
     * @param stats Pointer to the RTC engine statistics: RtcStats.
     */
    virtual void onRtcStats(const RtcStats& stats)  =0;


    /** Occurs when the engine receives and renders the first local video frame on the video window.

    @param width Width (pixels) of the first local video frame.
    @param height Height (pixels) of the first local video frame.
    @param elapsed Time elapsed (ms) from the local user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
    If you call the \ref IRtcEngine::startPreview "startPreview" method  before calling the *joinChannel* method, then @p elapsed is the time elapsed from calling the *startPreview* method until the SDK triggers this callback.
    */
    virtual void onFirstLocalVideoFrame(int width, int height, int elapsed) =0;

  
    /** Occurs when the first remote video frame is rendered.

    The SDK triggers this callback when the first frame of the remote video is displayed in the user's video window. The application can retrieve the time elapsed from a user joining the channel until the first video frame is displayed.

    @param userId User ID of the remote user sending the video stream.
    @param width Width (pixels) of the video frame.
    @param height Height (pixels) of the video stream.
    @param elapsed Time elapsed (ms) from the local user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
    */
    virtual void onFirstRemoteVideoFrame(const char* userId, int width, int height, int elapsed) =0;

    /** Occurs when the remote audio state changes.
     *
     * This callback indicates the state change of the remote audio stream.
     *
     * @param uid ID of the remote user whose audio state changes.
     * @param state State of the remote audio. See #REMOTE_AUDIO_STATE.
     * @param reason The reason of the remote audio state change.
     * See #REMOTE_AUDIO_STATE_REASON.
     * @param elapsed Time elapsed (ms) from the local user calling the
     * \ref IRtcEngine::joinChannel "joinChannel" method until the SDK
     * triggers this callback.
     */
    virtual void onRemoteAudioStateChanged(const char* uid, VK_REMOTE_AUDIO_STATE state, VK_REMOTE_AUDIO_STATE_REASON reason, int elapsed) {
        (void)uid;
        (void)state;
        (void)reason;
        (void)elapsed;
    }
    virtual void onRemoteVideoStateChanged(const char*  uid, VK_REMOTE_VIDEO_STATE state, VK_REMOTE_VIDEO_STATE_REASON reason, int elapsed) {
        (void)uid;
        (void)state;
        (void)reason;
        (void)elapsed;
    }

    /** Occurs when the audio mixing file playback finishes.

     **DEPRECATED**  use onAudioMixingStateChanged instead.

     You can start an audio mixing file playback by calling the \ref IRtcEngine::startAudioMixing "startAudioMixing" method. The SDK triggers this callback when the audio mixing file playback finishes.

     If the *startAudioMixing* method call fails, an error code returns in the \ref IRtcEngineEventHandler::onError "onError" callback.

     */
    virtual void onAudioMixingFinished() = 0;
    /** Occurs when the audio effect file playback finishes.


     You can start an audio effect file playback by calling the \ref playEffect  method. The SDK triggers this callback when the audio mixing file playback finishes.

     If the *playEffect* method call fails, an error code returns in the \ref IRtcEngineEventHandler::onError "onError" callback.

     */
    virtual void onAudioEffectFinished(int soundId) = 0;

    /** Occurs when the local record audio frame got.

     when local audio frame got,the function shoud be invoked

     */
    virtual bool onRecordAudioFrame(AudioFrame& audioFrame) = 0;
    /** Occurs when the local video frame got.

     when local video frame got,the function shoud be invoked

     */
    virtual bool onCaptureVideoFrame(const char* userId,VideoFrame& videoFrame) = 0;
     /** Occurs when the remote video frame got.

     when the remote video frame got,the function shoud be invoked

     */
    virtual bool onRenderVideoFrame(const char* userId, VideoFrame& videoFrame) = 0;
      /** Occurs when the local video stream state changes.

       @note This callback indicates the state of the local video stream, including camera capturing and video encoding, and allows you to troubleshoot issues when exceptions occur.

       @param localVideoState State type #VK_LOCAL_VIDEO_STREAM_STATE. When the state is VK_LOCAL_VIDEO_STREAM_STATE_FAILED (3), see the *error* parameter for details.
       @param error The detailed error information. code #VK_LOCAL_VIDEO_STREAM_ERROR.
       */
    virtual void onLocalVideoStateChanged(VK_LOCAL_VIDEO_STREAM_STATE localVideoState,VK_LOCAL_VIDEO_STREAM_ERROR error) = 0;
    /** Occurs when the local audio state changes.
     *
     * This callback indicates the state change of the local audio stream,
     * including the state of the audio recording and encoding, and allows
     * you to troubleshoot issues when exceptions occur.
     *
     * @note
     * When the state is #VK_LOCAL_AUDIO_STREAM_STATE_FAILED (3), see the `error`
     * parameter for details.
     *
     * @param state State of the local audio. See #VK_LOCAL_AUDIO_STREAM_STATE.
     * @param error The error information of the local audio.
     * See #VK_LOCAL_AUDIO_STREAM_ERROR.
     */
    virtual void onLocalAudioStateChanged(VK_LOCAL_AUDIO_STREAM_STATE state, VK_LOCAL_AUDIO_STREAM_ERROR error)=0;
    
    
    virtual void onStageResult(bool success) = 0;
    
};

/**
* Video device Manager methods.

 The IVideoDeviceManager interface class retrieves the video device information.
*/
class IVKVideoDeviceManager
{

public:
    /** Retrieves the total number of the indexed video devices in the system.

    @return Total number of the indexed video devices:
    */
    virtual int getCount() = 0;

    /** Retrieves a specified piece of information about an indexed video device.

     @param index The specified index of the video device that must be less than the return value of \ref IVideoDeviceCollection::getCount "getCount".
     @param deviceName Pointer to the video device name.
     @param deviceId Pointer to the video device ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getDevice(int index, char deviceName[VK_MAX_LENGTH], char deviceId[VK_MAX_LENGTH]) = 0;
    
    /** Specifies a device with the device ID.

     @param deviceId Pointer to the device ID of the device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setDevice(const char deviceId[VK_MAX_LENGTH]) = 0;


};





/** Audio device Manager methods.

The IAudioDeviceManager interface class retrieves device-related information.
*/
class IVKAudioDeviceManager
{

public:

    /** Retrieves the total number of audio playback or audio recording devices.

     @note You must first call the \ref IAudioDeviceManager::enumeratePlaybackDevices "enumeratePlaybackDevices" or \ref IAudioDeviceManager::enumerateRecordingDevices "enumerateRecordingDevices" method before calling this method to return the number of  audio playback or audio recording devices.

     @return Number of audio playback or audio recording devices.
     */
    virtual int getCount() = 0;

    /** Retrieves a specified piece of information about an indexed audio device.

     @param index The specified index that must be less than the return value of \ref IAudioDeviceCollection::getCount "getCount".
     @param deviceName Pointer to the audio device name.
     @param deviceId Pointer to the audio device ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getDevice(int index, char deviceName[VK_MAX_LENGTH], char deviceId[VK_MAX_LENGTH]) = 0;
    /** Specifies a device with the device ID.

     @param deviceId Pointer to the device ID of the device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setDevice(const char deviceId[VK_MAX_LENGTH]) = 0;
    /** Sets the volume of the microphone.

     @param volume Sets the volume of the microphone. The value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRecordingDeviceVolume(int volume) = 0;

    /** Retrieves the volume of the microphone.

     @param volume Pointer to the microphone volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getRecordingDeviceVolume(int *volume) = 0;

};

/** Definition of RtcEngineContext.
*/
struct RtcContext
{
    /** App ID issued to you by VIPKID. Apply for a new App ID from VIPKID if
     * it is missing from your kit.
     */
    const char* appId;
    VKWorkMode workmode;  // class type 0:1v1 1:broadCast
	void* context;        // reserved,user datas can pass from here
    RtcContext()
    /** The App ID issued to your project by VIPKID.
     */
    :appId(NULL)
    /** The video window handle. Once set, this parameter enables you to plug
     * or unplug the video devices while they are powered.
     */
    ,context(NULL)
    ,workmode(UNICAST)
    {}
};



/** IVKRtcEngine is the base interface class of the VIPKID SDK that provides the main VIPKID SDK methods invoked by your application.

Enable the VIPKID SDK's communication functionality through the creation of an IRtcEngine object, then call the methods of this object.
 */
class IVKRtcEngine
{

public:

    /** Initializes the VIPKID SDK service.
     *
     * Ensure that you call the
     * \ref VIPKID::rtc::createEngine
     * "createVKRtcEngine" and \ref VIPKID::rtc::IRtcEngine::initialize
     * "initialize" methods before calling any other API.
     *
     * @param context Pointer to the RTC engine context. See RtcEngineContext.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int initialize(const RtcContext& context) = 0;

    /** Releases all IRtcEngine resources.

     @param sync
     - true: (Synchronous call) The result returns after the IRtcEngine resources are released. The application should not call this method in the SDK generated callbacks. Otherwise, the SDK must wait for the callbacks to return to recover the associated IRtcEngine resources, resulting in a deadlock. The SDK automatically detects the deadlock and converts this method into an asynchronous call, causing the test to take additional time.
     - false: (Asynchronous call) The result returns immediately, even when the IRtcEngine resources have not been released. The SDK releases all resources.

     @note Do not immediately uninstall the SDK's dynamic library after the call, or it may cause a crash due to the SDK clean-up thread not quitting.
     */
    virtual void release(bool sync=false) = 0;

    /** Sets the sdk params.

     The method allow sdk to set spectify params

     @param key     identifier to be  saved inner map
     @param value value to be saved inner map
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setTrials(const char* key,const char* value) = 0;

    /** Allows a user to join a channel.

     Users in the same channel can talk to each other, and multiple users in the same channel can start a group chat. Users with different App IDs cannot call each other.


     You must call the \ref IRtcEngine::leaveChannel "leaveChannel" method to exit the current call before entering another channel.

     A successful \ref VIPKID::rtc::IRtcEngine::joinChannel "joinChannel" method call triggers the following callbacks:
     - The local client: \ref VIPKID::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess"
     - The remote client: \ref VIPKID::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" , if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.

     When the connection between the client and VIPKID's server is interrupted due to poor network conditions, the SDK tries reconnecting to the server. When the local client successfully rejoins the channel, the SDK triggers the \ref VIPKID::rtc::IRtcEngineEventHandler::onRejoinChannelSuccess "onRejoinChannelSuccess" callback on the local client.

     @note A channel does not accept duplicate uids, such as two users with the same @p uid. If you set @p uid as 0, the system automatically assigns a @p uid. If you want to join a channel from different devices, ensure that each device has a different uid.
     @warning Ensure that the App ID used for creating the token is the same App ID used by the \ref IRtcEngine::initialize "initialize" method for initializing the RTC engine. Otherwise, the CDN live streaming may fail.

     @param token Pointer to the token generated by the application server. In most circumstances, a static App ID suffices. For added security, use a Channel Key.
     - If the user uses a static App ID, *token* is optional and can be set as NULL.
     - If the user uses a Channel Key, VIPKID issues an additional App Certificate for you to generate a user key based on the algorithm and App Certificate for user authentication on the server.
     @param channelId Pointer to the unique channel name for the VIPKID RTC session in the string format smaller than 64 bytes. Supported characters:
     - The 26 lowercase English letters: a to z
     - The 26 uppercase English letters: A to Z
     - The 10 numbers: 0 to 9
     - The space
     - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","
     @param userId (Optional) User ID. A 32-bit unsigned integer with a value ranging from 1 to 2<sup>32</sup>-1. The @p uid must be unique. If a @p uid is not assigned (or set to 0), the SDK assigns and returns a @p uid in the \ref IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" callback. Your application must record and maintain the returned *uid* since the SDK does not do so.
     @param extInfo (Optional) Pointer to additional information about the channel. This parameter can be set to NULL or contain channel related information. Other users in the channel will not receive this message.

     @return
     - 0: Success.
     - < 0: Failure.
        - #ERR_INVALID_ARGUMENT (-2)
        - #ERR_NOT_READY (-3)
        - #ERR_REFUSED (-5)
     */
    virtual int joinChannel(const char* token, const char* channelId, const char* userId,const void* extInfo) = 0;


    /** Allows a user to leave a channel, such as hanging up or exiting a call.

     After joining a channel, the user must call the *leaveChannel* method to end the call before joining another channel.

     This method returns 0 if the user leaves the channel and releases all resources related to the call.

     This method call is asynchronous, and the user has not left the channel when the method call returns. Once the user leaves the channel, the SDK triggers the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback.

     A successful \ref VIPKID::rtc::IRtcEngine::leaveChannel "leaveChannel" method call triggers the following callbacks:
     - The local client: \ref VIPKID::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel"
     - The remote client: \ref VIPKID::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" , if the user leaving the channel is in the Communication channel, or is a BROADCASTER in the Live Broadcast profile.

     @note
     - If you call the \ref IRtcEngine::release "release" method immediately after the *leaveChannel* method, the *leaveChannel* process interrupts, and the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback is not triggered.
     - If you call the *leaveChannel* method during a CDN live streaming, the SDK triggers the \ref IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int leaveChannel() = 0;


    /** Retrieves the pointer to the device manager object.

     */
    virtual IVKVideoDeviceManager* videoDeviceManager() = 0;

    virtual IVKAudioDeviceManager* audioDeviceManager() = 0;


    /** Sets the video encoder configuration.

     Each video encoder configuration corresponds to a set of video parameters, including the resolution, frame rate, bitrate, and video orientation.

     The parameters specified in this method are the maximum values under ideal network conditions. If the video engine cannot render the video using the specified parameters due to poor network conditions, the parameters further down the list are considered until a successful configuration is found.

     @note If you do not need to set the video encoder configuration after joining the channel, you can call this method before the \ref IRtcEngine::enableVideo "enableVideo" method to reduce the render time of the first video frame.

     @param config Sets the local video encoder configuration. See VideoEncoderConfiguration.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setVideoEncoderConfiguration(const VideoEncoderConfiguration& config,LOCAL_VIDEO_STREAM_TYPE streamType) = 0;
    
    /** open the camera preview ,but not publish the video.

      this method only open the specified deviceID camera,if user want to push the video shoud use mute
     muteLocalVideoStream function
     @param deviceID to preview only for pc ,android and ios deviceID is nullptr,use front camera default
     @param handle   Distinguish cameras between [privew]  and [setting]
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int openCamera(const char* deviceID,void* handle) = 0;
    /** Stops the local video preview .
     @param  handle tell me close which camera [privew] or [setting]

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int closeCamera(const char* handle) = 0;
    
   
    /** Sets the stream mode to the single-stream (default) or dual-stream mode. (Live broadcast only.)

     If the dual-stream mode is enabled, the receiver can choose to receive the high stream (high-resolution and high-bitrate video stream), or the low stream (low-resolution and low-bitrate video stream).

     @param enabled Sets the stream mode:
     - true: Dual-stream mode.
     - false: (Default) Single-stream mode.
     */
    virtual int enableDualStreamMode(bool enabled) = 0;

	
    /** Stops/Resumes sending the local audio stream.

     A successful \ref VIPKID::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" method call triggers the \ref VIPKID::rtc::IRtcEngineEventHandler::onUserMuteAudio "onUserMuteAudio" callback on the remote client.
     @note When @p mute is set as @p true, this method does not disable the microphone, which does not affect any ongoing recording.

     @param mute Sets whether to switch audio:
     - true: Stops local audio record.
     - false: (Default) start local audio record.
     @param publish Sets whether to publish local audio stream
     - true:  start publish local audio stream to the channel
     - false: stop publish local audio stream to the channel
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int muteLocalAudioStream(bool mute,bool publish) = 0;
    /** Stops/Resumes receiving all remote users' audio streams.

     @param mute Sets whether to receive/stop receiving all remote users' audio streams.
     - true: Stops receiving all remote users' audio streams.
     - false: (Default) Receives all remote users' audio streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int muteAllRemoteAudioStreams(bool mute) = 0;
    
    /** Stops/Resumes receiving a specified remote user's audio stream.

     @note If you called the \ref VIPKID::rtc::IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams" method and set @p mute as @p true to stop receiving all remote users' audio streams, call the *muteAllRemoteAudioStreams* method and set @p mute as @p false before calling this method. The *muteAllRemoteAudioStreams* method sets all remote audio streams, while the *muteRemoteAudioStream* method sets a specified remote audio stream.

     @param userId User ID of the specified remote user sending the audio.
     @param mute Sets whether to receive/stop receiving a specified remote user's audio stream:
     - true: Stops receiving the specified remote user's audio stream.
     - false: (Default) Receives the specified remote user's audio stream.

     @return
     - 0: Success.
     - < 0: Failure.

     */
	virtual int muteRemoteAudioStream(const char* userId, bool mute) = 0;
    /** Stops/Resumes sending the local video stream.

     A successful \ref VIPKID::rtc::IRtcEngine::muteLocalVideoStream "muteLocalVideoStream" method call triggers the \ref VIPKID::rtc::IRtcEngineEventHandler::onUserMuteVideo "onUserMuteVideo" callback on the remote client.
     @note When set to *true*, this method does not disable the camera which does not affect the retrieval of the local video streams. This method executes faster than the \ref VIPKID::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo" method which controls the sending of the local video stream.

     @param mute Sets whether to send/stop sending the local video stream:
     - true: Stop sending the local video stream.
     - false: (Default) Send the local video stream.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int muteLocalVideoStream(bool mute) = 0;

    /** Stops/Resumes receiving all remote users' video streams.

     @param  mute Sets whether to receive/stop receiving all remote users' video streams:
     - true: Stop receiving all remote users' video streams.
     - false: (Default) Receive all remote users' video streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int muteAllRemoteVideoStreams(bool mute) = 0;

    /** Stops/Resumes receiving a specified remote user's video stream.

     @note If you called the \ref VIPKID::rtc::IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" method and set @p mute as @p true to stop receiving all remote video streams, call the *muteAllRemoteVideoStreams* method and set @p mute as @p false before calling this method.

     @param userId User ID of the specified remote user.
     @param mute Sets whether to receive/stop receiving the specified remote user's video stream:
     - true: Stop receiving the specified remote user's video stream.
     - false: (Default) Receive the specified remote user's video stream.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int muteRemoteVideoStream(const char* userId, bool mute) = 0;
    /** Sets the remote user's video stream type received by the local user when the remote user sends dual streams.

     This method allows the application to adjust the corresponding video-stream type based on the size of the video window to reduce the bandwidth and resources.

     - If the remote user enables the dual-stream mode by calling the \ref VIPKID::rtc::IRtcEngine::enableDualStreamMode "enableDualStreamMode" method, the SDK receives the high-stream video by default.
     - If the dual-stream mode is not enabled, the SDK receives the high-stream video by default.

     The method result returns in the \ref VIPKID::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" callback. The SDK receives the high-stream video by default to reduce the bandwidth. If needed, users may use this method to switch to the low-stream video.
     By default, the aspect ratio of the low-stream video is the same as the high-stream video. Once the resolution of the high-stream video is set, the system automatically sets the resolution, frame rate, and bitrate of the low-stream video.

     @param userId ID of the remote user sending the video stream.
     @param streamType  Sets the video-stream type. See #REMOTE_VIDEO_STREAM_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setRemoteVideoStreamType(const char* userId, REMOTE_VIDEO_STREAM_TYPE streamType) = 0;
  


    /** Starts playing and mixing the music file.

     This method mixes the specified local audio file with the audio stream from the microphone, or replaces the microphone's audio stream with the specified local audio file. You can choose whether the other user can hear the local audio playback and specify the number of playback loops. This method also supports online music playback.

     When the audio mixing file playback finishes after calling this method, the SDK triggers the \ref VIPKID::rtc::IRtcEngineEventHandler::onAudioMixingFinished "onAudioMixingFinished" callback.

     A successful \ref VIPKID::rtc::IRtcEngine::startAudioMixing "startAudioMixing" method call triggers the \ref VIPKID::rtc::IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (PLAY) callback on the local client.

     When the audio mixing file playback finishes, the SDK triggers the \ref VIPKID::rtc::IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (STOPPED) callback on the local client.
     @note
     - Call this method when you are in a channel.
     - If the local audio mixing file does not exist, or if the SDK does not support the file format or cannot access the music file URL, the SDK returns WARN_AUDIO_MIXING_OPEN_ERROR = 701.

     @param filePath Pointer to the absolute path of the local or online audio file to mix. Supported audio formats: 3GP, ASF, ADTS, AVI, MP3, MPEG-4, SAMI, and WAVE. For more information, see [Supported Media Formats in Media Foundation](https://docs.microsoft.com/en-us/windows/desktop/medfound/supported-media-formats-in-media-foundation).
     @param loopback Sets which user can hear the audio mixing:
     - true: Only the local user can hear the audio mixing.
     - false: Both users can hear the audio mixing.
     @param cycle Sets the number of playback loops:
     - Positive integer: Number of playback loops.
     - -1: Infinite playback loops.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int startAudioMixing(const char* filePath, bool loopback,int cycle) = 0;
    /** Stops playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int stopAudioMixing() = 0;
    /** Pauses playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int pauseAudioMixing() = 0;
    /** Resumes playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int resumeAudioMixing() = 0;
    /** Adjusts the volume during audio mixing.

     Call this method when you are in a channel.

     @param volume Audio mixing volume. The value ranges between 0 and 100 (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int adjustAudioMixingVolume(int volume) = 0;


    /** Retrieves the duration (ms) of the music file.

     Call this method when you are in a channel.

     @return
     - &ge; 0: The audio mixing duration, if this method call succeeds.
     - < 0: Failure.
     */
	virtual int getAudioMixingDuration() = 0;
    /** Retrieves the playback position (ms) of the music file.

     Call this method when you are in a channel.

     @return
     - &ge; 0: The current playback position of the audio mixing, if this method call succeeds.
     - < 0: Failure.
     */
	virtual int getAudioMixingCurrentPosition() = 0;
    /** Sets the playback position of the music file to a different starting position (the default plays from the beginning).

     @param pos The playback starting position (ms) of the music file.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setAudioMixingPosition(int pos /*in ms*/) = 0;
    /** Sets the volume of a specified audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @param volume Sets the volume of the specified audio effect. The value ranges between 0 and 100 (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setVolumeOfEffect(int soundId, int volume) = 0;

    /** Plays a specified local or online audio effect file.

     This method allows you to set the loop count, pitch, pan, and gain of the audio effect file, as well as whether the remote user can hear the audio effect.

     To play multiple audio effect files simultaneously, call this method multiple times with different soundIds and filePaths. We recommend playing no more than three audio effect files at the same time.

     @param soundId ID of the specified audio effect. Each audio effect has a unique ID.

     @note
     - If the audio effect is preloaded into the memory through the \ref IRtcEngine::preloadEffect "preloadEffect" method, the value of @p soundID must be the same as that in the *preloadEffect* method.
     - Playing multiple online audio effect files simultaneously is not supported on macOS and Windows.

     @param filePath The absolute path to the local audio effect file or the URL of the online audio effect file.
     @param startPos The  .audio effect display start position. default 0

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int playEffect(int soundId, const char* filePath ,int startPos = 0) = 0;
    /** Stops playing a specified audio effect.

     @param soundId ID of the audio effect to stop playing. Each audio effect has a unique ID.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int stopEffect(int soundId) = 0;

    /** Pauses a specified audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int pauseEffect(int soundId) = 0;

    /** Resumes playing a specified audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int resumeEffect(int soundId) = 0;
    /** register a handler to receive  statue messages and av data.

     @param engineHandler callback.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   
    virtual bool registerEngineHandler(IVKRtcEngineHandler *engineHandler) = 0;

    /** Gets a the *ISubChannel* object.
     @param channelId Channel ID of the RTC connection.
     @return Pointer to the *ISubChannel* object. If the connection hasn't been created, NULL will be returned.
     */
    virtual ISubChannel* createSubChannel(const char *channelId) = 0;
    /** just for record class.let one user on stage
     @param userId the stage user.
     */
    virtual void setStage(bool on){};
};

};


#endif
