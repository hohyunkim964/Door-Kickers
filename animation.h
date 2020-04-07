#pragma once
class animation
{
private:

	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;			//프레임 플레이 목록

	_vFrameList _frameList;					//프레임위치목록
	_vPlayList _playList;					//플레이 목록

	int _frameNum;							//프레임 갯수
	int _frameWidth;
	int _frameHeight;

	bool _loop;
	bool _play;

	float _frameUpdateSec;					//프레임 업데이트
	float _elapsedSec;						//프레임 경과시간
	DWORD _nowPlayIndex;					//현재 플레이 인덱스
public:
	animation();
	~animation();


	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	//처음부터 끝까지 애니메이션 셋팅
	void setDefPlayFrame(bool reverse = false, bool loop = false);
	//배열에 담겨져 있는 애들만
	void setPlayFrame(int* playArr, int arrLen, bool loop = false);
	//시작과 끝구간을 정해서
	void setPlayFrame(int start, int end, bool reverse =  false, bool loop = false);

	//초당 갱신 횟수
	void setFPS(int framePerSec);

	//프레임 업데이트 타임
	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline bool isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }
	


};

