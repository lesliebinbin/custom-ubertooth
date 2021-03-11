require_relative 'ubertooth_ext'
def main
  handler = UbertoothExt.new
  producer = Thread.new do
    loop do
      result = handler.start_my_ubertooth(1, 1, 1200, 123, 123, 123)
      puts result
    end
  end
  consumer = Thread.new do
    loop do
      sleep 3
      result = handler.get_ubertooth_items
      puts result
    end
  end
  producer.join
  consumer.join
end
main if $PROGRAM_NAME == __FILE__
