static void
iter_<%=c_func%>(na_loop_t *const lp)
{
    size_t   i;
    char    *p1;
    ssize_t  s1;
    size_t  *idx1;
    double   x;
    <%=struct%> *w = (<%=struct%>*)(lp->opt_ptr);
    <% c_args = get(:postpose) ? "x,w" : "w,x" %>

    INIT_COUNTER(lp, i);
    INIT_PTR_IDX(lp, 0, p1, s1, idx1);

    if (idx1) {
        for (; i--;) {
            GET_DATA_INDEX(p1,idx1,double,x);
            <%=func_name%>(<%=c_args%>);
        }
    } else {
        for (; i--;) {
            GET_DATA_STRIDE(p1,s1,double,x);
            <%=func_name%>(<%=c_args%>);
        }
    }
}

/*
  @overload <%=name%>(<%=args[1][1]%>)
  @param  [DFloat]   <%=args[1][1]%>
  @return [<%=class_name%>]  self

  <%= description %>
*/
static VALUE
<%=c_func(1)%>(VALUE self, VALUE v1)
{
    <%=struct%> *w;
    ndfunc_arg_in_t ain[1] = {{cDF,0}};
    ndfunc_t ndf = {iter_<%=c_func%>, FULL_LOOP, 1,0, ain,0};

    TypedData_Get_Struct(self, <%=struct%>, &<%=data_type_var%>, w);

    na_ndloop3(&ndf, w, 1, v1);
    return self;
}
