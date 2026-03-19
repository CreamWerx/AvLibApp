extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
//#include <libavutil/avutil.h>
//#include <libswscale/swscale.h>
}

#include <iostream>
#include <filesystem>


int main()
{
	AVFormatContext* pformatContext = nullptr;

	if (avformat_open_input(&pformatContext, "sample.mp4", nullptr, nullptr) != 0)
	{
		std::cout << "Could not open file\n";
		return -1;
	}
	std::cout << "Opened file successfully\n";

	AVCodecParameters* pcodecParameters;
	const AVCodec* pcodec = new AVCodec;

	for (int i = 0; i < pformatContext->nb_streams; i++)
	{
		pcodecParameters = pformatContext->streams[i]->codecpar;
		pcodec = avcodec_find_decoder(pcodecParameters->codec_id);
		if (pcodec)
		{
			std::cout << "Found codec: " << pcodec->name << "\n";
			//only want video stream for now
			break;
		}
		else
		{
			std::cout << "Codec not found for stream " << i << "\n";
		}
	}

	AVCodecContext* pcodecContext = avcodec_alloc_context3(pcodec);
	if (!pcodecContext)
	{
		std::cout << "Could not allocate codec context\n";
		return -1;
	}



	pcodecContext = NULL;
	pcodec = NULL;
	avformat_close_input(&pformatContext);


}