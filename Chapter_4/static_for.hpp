
template<size_t for_start, size_t for_end, typename functor, size_t sequence_width,
typename... functor_types>
struct static_for_impl
{
    static inline void loop(functor_types&&... functor_args)
    {
      // The main sequence point is created, and then we call "next" on each point inside
      using sequence = point<for_start, for_end>;
      next<sequence>
        (std::integral_constant<bool, sequence::is_end_point_>(),
        std::forward<functor_types>(functor_args)...);
    }

private:
    template<size_t pt_start, size_t pt_end> struct point
    {
      static constexpr size_t start_        { pt_start };
      static constexpr size_t end_          { pt_end };
      static constexpr size_t count_        { end_ - start_ + 1 };
      static constexpr bool is_end_point_   { count_ <= sequence_width };

      static constexpr size_t sequence_count()
      {
        return points_in_sequence(sequence_width) > sequence_width ? sequence_width : points_in_sequence(sequence_width);
      }
      private:
        static constexpr size_t child_start(size_t index)
        {
          return index == 0 ? pt_start : child_end(index - 1) + 1;
        }
        static constexpr size_t child_end(size_t index)
        {
          return index == sequence_count() - 1 ? pt_end : pt_start + points_in_sequence(sequence_count()) * (index + 1) - (index < count_ ? 1 : 0);
        }
        static constexpr size_t points_in_sequence(size_t max)
        {
          return count_ / max + ((count_ % max) > 0 ? 1 : 0);
        }

    public:
      template<size_t index> using child_point = point<child_start(index), child_end(index)>;
};


template<size_t flat_start, size_t flat_end, class flat_functor> struct flat_for
{
  static inline void flat_loop(functor_types&&... functor_args)
  {
    flat_next(std::integral_constant<size_t, flat_start>(), std::forward<functor_types>(functor_args)...);
  }

  private:
    static inline void flat_next(std::integral_constant<size_t, flat_end + 1>, functor_types&&...){}
    template<size_t index>

    static inline void flat_next(std::integral_constant<size_t, index>, functor_types&&... functor_args)
    {
      flat_functor::template func<index>(std::forward<functor_types>(functor_args)...);
      flat_next(std::integral_constant<size_t, index + 1>(), std::forward<functor_types>(functor_args)...);
    }
};


template<typename sequence> struct flat_sequence
{
  template<size_t index> static inline void func(functor_types&&... functor_args)
  {
    using pt = typename sequence::template child_point<index>;
    next<pt>
    (std::integral_constant<bool, pt::is_end_point_>(), std::forward<functor_types>(functor_args)...);
  }
};


template<typename sequence> static inline void next(std::true_type, functor_types&&... functor_args)
{
  flat_for<sequence::start_, sequence::end_, functor>::flat_loop(std::forward<functor_types>(functor_args)...);
}

template<typename sequence> static inline void next(std::false_type, functor_types&&... functor_args)
{
  flat_for<0, sequence::sequence_count() - 1, flat_sequence<sequence>>::flat_loop(std::forward<functor_types>(functor_args)...);
}
};

template<size_t count, typename functor, size_t sequence_width = 70,
typename... functor_types>
inline void static_for(functor_types&&... functor_args)
{
  static_for_impl<0, count-1, functor, sequence_width, functor_types...>::loop(std::forward<functor_types>(functor_args)...);
}

template<size_t start, size_t end, typename functor, size_t sequence_width = 70,
typename... functor_types>
inline void static_for(functor_types&&... functor_args)
{
  static_for_impl<start, end, functor, sequence_width, functor_types...>::loop(std::forward<functor_types>(functor_args)...);
}
