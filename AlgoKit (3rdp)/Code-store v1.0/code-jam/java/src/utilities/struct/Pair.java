/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package utilities.struct;

import java.io.*;
import java.util.*;

/**
 * A basic mutable Object pair.
 * 
 * <p>
 * #ThreadSafe# if the objects are threadsafe
 * </p>
 * 
 * @since Lang 3.0
 * @author Matt Benson
 * @version $Id: Pair.java 967237 2010-07-23 20:08:57Z mbenson $
 */
public class Pair<L, R>
    extends AbstractList<Object>
    implements List<Object>, Serializable
{
    /**
     * 
     */
    private static final long serialVersionUID = 1L;

    /** Left object */
    public L first;

    /** Right object */
    public R second;

    /**
     * Create a new Pair instance.
     * 
     * @param left
     * @param right
     */
    public Pair(L left, R right)
    {
        this.first = left;
        this.second = right;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public boolean equals(Object obj)
    {
        if (obj == this) {
            return true;
        }
        if (obj instanceof Pair<?, ?> == false) {
            return false;
        }
        Pair<?, ?> other = (Pair<?, ?>) obj;
        return equals(first, other.first) && equals(second, other.second);
    }

    // Null-safe equals()
    // -----------------------------------------------------------------------
    /**
     * <p>
     * Compares two objects for equality, where either one or both objects may
     * be <code>null</code>.
     * </p>
     * 
     * <pre>
     * ObjectUtils.equals(null, null)                  = true
     * ObjectUtils.equals(null, "")                    = false
     * ObjectUtils.equals("", null)                    = false
     * ObjectUtils.equals("", "")                      = true
     * ObjectUtils.equals(Boolean.TRUE, null)          = false
     * ObjectUtils.equals(Boolean.TRUE, "true")        = false
     * ObjectUtils.equals(Boolean.TRUE, Boolean.TRUE)  = true
     * ObjectUtils.equals(Boolean.TRUE, Boolean.FALSE) = false
     * </pre>
     * 
     * @param object1 the first object, may be <code>null</code>
     * @param object2 the second object, may be <code>null</code>
     * @return <code>true</code> if the values of both objects are the same
     */
    public static boolean equals(Object object1, Object object2)
    {
        if (object1 == object2) {
            return true;
        }
        if ((object1 == null) || (object2 == null)) {
            return false;
        }
        return object1.equals(object2);
    }

    private static int hashcode(Object o)
    {
        return o == null ? 0 : o.hashCode();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public int hashCode()
    {
        return 31 * hashcode(first) + hashcode(second);
    }

    /**
     * Returns a String representation of the Pair in the form: (L,R)
     */
    @Override
    public String toString()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("(");
        builder.append(first);
        builder.append(",");
        builder.append(second);
        builder.append(")");
        return builder.toString();
    }

    @SuppressWarnings("unchecked")
    public static <L, R> Pair<L, R> of(L left)
    {
        return new Pair<L, R>(left, (R) left);
    }

    /**
     * Static creation method for a Pair<L, R>.
     * 
     * @param <L>
     * @param <R>
     * @param left
     * @param right
     * @return Pair<L, R>(left, right)
     */
    public static <L, R> Pair<L, R> of(L left, R right)
    {
        return new Pair<L, R>(left, right);
    }

    @Override
    public Object get(int index)
    {
        switch (index) {
        case 0:
            return this.first;
        case 1:
            return this.second;
        }
        throw new IndexOutOfBoundsException();
    }

    @Override
    public int size()
    {
        return 2;
    }
}
