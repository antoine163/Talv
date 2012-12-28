//22/12/12

#include "tts.hpp"
#include <gst/gst.h>

#include <iostream>

Tts::Tts(wxString& lg, wxString& msg) : _lg (lg), _msg(msg)
{
	Create();
	Run();
}

Tts::~Tts()
{
}

wxThread::ExitCode Tts::Entry()
{
	GstElement *pipeline;
	GstBus *bus;
	GstMessage *msg;
  
	/* Build the pipeline */
	pipeline = gst_parse_launch("playbin uri=\"http://translate.google.com/translate_tts?ie=UTF-8&tl="+_lg+"&q="+_msg+"\"", NULL);
	
	/* Start playing */
	gst_element_set_state(pipeline, GST_STATE_PLAYING);
	
	/* Wait until error or EOS */
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
	
	/* Free resources */
	if(msg != NULL)
		gst_message_unref(msg);
	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
  
	return (wxThread::ExitCode)0;
}
