#include <babeltrace/ctf-writer/writer.h>
#include <babeltrace/ctf-writer/clock.h>
#include <babeltrace/ctf-writer/stream.h>
#include <babeltrace/ctf-writer/event.h>
#include <babeltrace/ctf-writer/event-types.h>
#include <babeltrace/ctf-writer/event-fields.h>
#include <assert.h>

int push_unaligned_integer_event(struct bt_ctf_stream_class *stream_class,
	struct bt_ctf_stream *stream)
{
	int ret = 0;
	struct bt_ctf_event_class *unaligned_int_event_class = NULL;
	struct bt_ctf_event *unaligned_int_event = NULL;
	struct bt_ctf_field_type *uint_14_t = NULL;
	struct bt_ctf_field *uint_14_value = NULL;

	assert(stream_class && stream);
	unaligned_int_event_class = bt_ctf_event_class_create(
		"unaligned_int_event");
	if (!unaligned_int_event) {
		ret = -1;
		goto end;
	}

	uint_14_t = bt_ctf_field_type_integer_create(14);
	if (!uint_14_t) {
		ret = -1;
		goto end;
	}

	ret = bt_ctf_event_class_add_field(unaligned_int_event_class, uint_14_t,
		"uint_14");
	if (ret) {
		goto end;
	}

	ret = bt_ctf_stream_class_add_event_class(stream_class,
		unaligned_int_event_class);
	if (ret) {
		goto end;
	}

	unaligned_int_event = bt_ctf_event_create(unaligned_int_event_class);
	if (!unaligned_int_event) {
		goto end;
	}

	uint_14_value = bt_ctf_event_get_payload(unaligned_int_event,
		"uint_14");
	ret = bt_ctf_field_unsigned_integer_set_value(uint_14_value, 42);
	if (ret) {
		goto end;
	}

	ret = bt_ctf_stream_append_event(stream, unaligned_int_event);
end:
	bt_ctf_event_class_put(unaligned_int_event_class);
	bt_ctf_event_put(unaligned_int_event);
	bt_ctf_field_type_put(uint_14_t);
	bt_ctf_field_put(uint_14_value);
	return ret;
}

int main(int argc, char **argv)
{
	int ret = 0;
	char trace_path[] = "/tmp/ctf_test_XXXXXX";
	struct bt_ctf_writer *writer = NULL;
	struct bt_ctf_clock *clock = NULL;
	struct bt_ctf_stream_class *stream_class = NULL;
	struct bt_ctf_stream *stream = NULL;

	if (!mkdtemp(trace_path)) {
		perror("# perror");
	}

	writer = bt_ctf_writer_create(trace_path);
	if (!writer) {
		ret = -1;
		goto end;
	}

	clock = bt_ctf_clock_create("a_clock");
	if (!clock) {
		ret = -1;
		goto end;
	}

	ret = bt_ctf_writer_add_clock(writer, clock);
	if (ret) {
		goto end;
	}

	stream_class = bt_ctf_stream_class_create("test_stream");
	if (!stream_class) {
		ret = -1;
		goto end;
	}

	stream = bt_ctf_writer_create_stream(writer, stream_class);
	if (!stream) {
		ret = -1;
		goto end;
	}

	/* Push an event containing a single 14-bit integer. */
	ret = push_unaligned_integer_event(stream_class, stream);
	if (ret) {
		goto end;
	}

	/* Push an event containing a float */

	/* Push an event containing a double */

	/* Push an event containing an array of floats */

end:
	bt_ctf_clock_put(clock);
	bt_ctf_stream_class_put(stream_class);
	bt_ctf_stream_put(stream);
	bt_ctf_writer_put(writer);
	return ret;
}
