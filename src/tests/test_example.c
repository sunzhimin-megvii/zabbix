/*
** Zabbix
** Copyright (C) 2001-2017 Zabbix SIA
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**/

#include "zbxtests.h"

#include "../libs/zbxdbcache/valuecache.h"

int	__wrap_zbx_vc_get_value_range(zbx_uint64_t itemid, int value_type, zbx_vector_history_record_t *values,
		int seconds, int count, int timestamp)
{
	zbx_history_record_t	*record = (zbx_history_record_t *) mock();

	zbx_vector_history_record_append(values, *record);

	return SUCCEED;
}

void test_exception()
{
	char	*str = NULL;
	*str = '0';
}

void test_successful_evaluate_function()
{
	int     ret;
	char    value[100], *error = NULL;
	DC_ITEM item = {.value_type = ITEM_VALUE_TYPE_UINT64};

	history_value_t		h_value = {.ui64 = 1024};
	zbx_history_record_t	record = {.value = h_value};

	will_return(__wrap_zbx_vc_get_value_range, &record);

	ret = evaluate_function(value, &item, "last", "", 1, &error);

	assert_int_equal(ret, SUCCEED);
}
