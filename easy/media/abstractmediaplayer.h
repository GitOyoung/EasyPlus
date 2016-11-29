#ifndef _ABSTRACT_MEDIA_PLAYER_H
#define _ABSTRACT_MEDIA_PLAYER_H

namespace easy {
	namespace media {
		class AbstractMediaPlayer
        {
        public:
            virtual bool start() = 0;
            virtual bool pause() = 0;
            virtual bool recovery() = 0;
            virtual bool stop() = 0;
            virtual int speedAdjust(int) = 0;
            virtual bool jump(int time) = 0;
            virtual bool move(int offset) = 0;

            virtual ~AbstractMediaPlayer() {}
        };

	}
}



#endif
