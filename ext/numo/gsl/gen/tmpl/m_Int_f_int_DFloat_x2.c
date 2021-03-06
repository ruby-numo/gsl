static void
iter_<%=c_func%>(na_loop_t *const lp)
{
    size_t   i;
    char    *p1, *p2, *p3;
    ssize_t  s1, s2, s3;
    double   x, y;
    int      z;
    int     *opts;

    INIT_COUNTER(lp, i);
    INIT_PTR(lp, 0, p1, s1);
    INIT_PTR(lp, 1, p2, s2);
    INIT_PTR(lp, 2, p3, s3);
    opts = (int*)(lp->opt_ptr);

    for (; i--; ) {
        GET_DATA_STRIDE(p1,s1,double,x);
        GET_DATA_STRIDE(p2,s2,double,y);
        z = <%=func_name%>(opts[0],x,y);
        SET_DATA_STRIDE(p3,s3,int,z);
    }
}

/*
  @overload <%=name%>(<%=args.map{|a| a[1]}.join(",")%>)
  @param  [Integer]  <%=args[0][1]%> parameter
  @param  [DFloat]   <%=args[1][1]%>
  @param  [DFloat]   <%=args[2][1]%>
  @return [Int]      result

  <%= description %>
*/
static VALUE
<%=c_func(3)%>(VALUE mod, VALUE v0, VALUE v1, VALUE v2)
{
    ndfunc_arg_in_t ain[2] = {{cDF,0},{cDF,0}};
    ndfunc_arg_out_t aout[1] = {{cI,0}};
    ndfunc_t ndf = {iter_<%=c_func%>, STRIDE_LOOP|NDF_EXTRACT, 2,1, ain,aout};
    int opts[1];

    opts[0] = NUM2INT(v0);

    return na_ndloop3(&ndf, opts, 2, v1, v2);
}
