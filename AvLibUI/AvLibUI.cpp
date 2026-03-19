extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
}

#include <iostream>
#include <filesystem>


int main()
{
	AVFormatContext* formatContext = nullptr;

	if (avformat_open_input(&formatContext, "sample.mp4", nullptr, nullptr) != 0)
	{
		std::cout << "Could not open file\n";
		return -1;
	}
	std::cout << "Opened file successfully\n";

	AVCodecParameters* codecParameters;
	const AVCodec* codec = new AVCodec;

	for (int i = 0; i < formatContext->nb_streams; i++)
	{
		codecParameters = formatContext->streams[i]->codecpar;
		codec = avcodec_find_decoder(codecParameters->codec_id);
		if (codec)
		{
			std::cout << "Found codec: " << codec->name << "\n";
			//only want video stream for now
			break;
		}
		else
		{
			std::cout << "Codec not found for stream " << i << "\n";
		}
	}

	AVCodecContext* codecContext = avcodec_alloc_context3(codec);
	if (!codecContext)
	{
		std::cout << "Could not allocate codec context\n";
		return -1;
	}



	codecContext = NULL;
	codec = NULL;
	avformat_close_input(&formatContext);


}