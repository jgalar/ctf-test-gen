#include <babeltrace/ctf-writer/writer.h>
#include <babeltrace/ctf-writer/clock.h>
#include <babeltrace/ctf-writer/stream.h>
#include <babeltrace/ctf-writer/event.h>
#include <babeltrace/ctf-writer/event-types.h>
#include <babeltrace/ctf-writer/event-fields.h>
#include <float.h>
#include <assert.h>
#include <limits.h>

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
	if (!unaligned_int_event_class) {
		ret = -1;
		goto end;
	}

	uint_14_t = bt_ctf_field_type_integer_create(14);
	if (!uint_14_t) {
		ret = -1;
		goto end;
	}

	ret = bt_ctf_field_type_set_alignment(uint_14_t, 1);
	if (ret) {
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

int push_float_event(struct bt_ctf_stream_class *stream_class,
	struct bt_ctf_stream *stream)
{
	int ret = 0;
	struct bt_ctf_event_class *float_event_class = NULL;
	struct bt_ctf_event *float_event = NULL;
	struct bt_ctf_field_type *float_t = NULL;
	struct bt_ctf_field *float_value = NULL;

	assert(stream_class && stream);
	float_event_class = bt_ctf_event_class_create(
		"float_event");
	if (!float_event_class) {
		ret = -1;
		goto end;
	}

	float_t = bt_ctf_field_type_floating_point_create();
	if (!float_t) {
		ret = -1;
		goto end;
	}

	ret = bt_ctf_field_type_set_alignment(float_t, 1);
	if (ret) {
		goto end;
	}
	ret = bt_ctf_event_class_add_field(float_event_class, float_t,
		"a_float");
	if (ret) {
		goto end;
	}

	ret = bt_ctf_stream_class_add_event_class(stream_class,
		float_event_class);
	if (ret) {
		goto end;
	}

	float_event = bt_ctf_event_create(float_event_class);
	if (!float_event) {
		goto end;
	}

	float_value = bt_ctf_event_get_payload(float_event,
		"a_float");
	ret = bt_ctf_field_floating_point_set_value(float_value, 3.1415);
	if (ret) {
		goto end;
	}

	ret = bt_ctf_stream_append_event(stream, float_event);
end:
	bt_ctf_event_class_put(float_event_class);
	bt_ctf_event_put(float_event);
	bt_ctf_field_type_put(float_t);
	bt_ctf_field_put(float_value);
	return ret;
}

int push_double_event(struct bt_ctf_stream_class *stream_class,
	struct bt_ctf_stream *stream)
{
	int ret = 0;
	struct bt_ctf_event_class *double_event_class = NULL;
	struct bt_ctf_event *double_event = NULL;
	struct bt_ctf_field_type *double_t = NULL;
	struct bt_ctf_field *double_value = NULL;

	assert(stream_class && stream);
	double_event_class = bt_ctf_event_class_create(
		"double_event");
	if (!double_event_class) {
		ret = -1;
		goto end;
	}

	double_t = bt_ctf_field_type_floating_point_create();
	if (!double_t) {
		ret = -1;
		goto end;
	}

	ret = bt_ctf_field_type_floating_point_set_exponent_digits(double_t,
		sizeof(double) * CHAR_BIT - DBL_MANT_DIG);
	if (ret) {
		goto end;
	}

	ret = bt_ctf_field_type_floating_point_set_mantissa_digits(double_t,
		DBL_MANT_DIG);
	if (ret) {
		goto end;
	}

	ret = bt_ctf_field_type_set_alignment(double_t, 1);
	if (ret) {
		goto end;
	}
	ret = bt_ctf_event_class_add_field(double_event_class, double_t,
		"a_double");
	if (ret) {
		goto end;
	}

	ret = bt_ctf_stream_class_add_event_class(stream_class,
		double_event_class);
	if (ret) {
		goto end;
	}

	double_event = bt_ctf_event_create(double_event_class);
	if (!double_event) {
		goto end;
	}

	double_value = bt_ctf_event_get_payload(double_event,
		"a_double");
	ret = bt_ctf_field_floating_point_set_value(double_value, 1.23456789);
	if (ret) {
		goto end;
	}

	ret = bt_ctf_stream_append_event(stream, double_event);
end:
	bt_ctf_event_class_put(double_event_class);
	bt_ctf_event_put(double_event);
	bt_ctf_field_type_put(double_t);
	bt_ctf_field_put(double_value);
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
	ret = push_float_event(stream_class, stream);
	if (ret) {
		goto end;
	}

	/* Push an event containing a double */
	ret = push_double_event(stream_class, stream);
	if (ret) {
		goto end;
	}

	bt_ctf_stream_flush(stream);
end:
	bt_ctf_clock_put(clock);
	bt_ctf_stream_class_put(stream_class);
	bt_ctf_stream_put(stream);
	bt_ctf_writer_put(writer);
	return ret;
}
