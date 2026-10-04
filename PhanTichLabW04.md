# Phân tích và giải bài Lab W04

**Đề bài:** Hệ thống tính lương và thưởng nhân sự trong `lab w04.pdf` được cung cấp.

**Ngôn ngữ:** C++11. **Phạm vi:** thu nhập hằng tháng trước khấu trừ, theo đúng ba công thức trong đề.

## 1. Yêu cầu cần hoàn thành

Bài gồm ba phần: **A - phân tích và thiết kế**, **B - cài đặt**, **C - kiểm thử và giải thích**. Chỉ viết công thức tính lương chưa đủ để hoàn thành bài.

| Nhóm yêu cầu | Nội dung bắt buộc | Cách thực hiện |
| --- | --- | --- |
| A.1-A.3 | Năm lớp và dữ liệu của ba loại nhân sự | `Employee`, ba lớp dẫn xuất, `Payroll` |
| A.4 | Nạp chồng constructor, tái sử dụng kiểm tra dữ liệu | Mỗi lớp nhân sự có hai constructor; constructor rút gọn ủy quyền cho constructor đầy đủ |
| A.5 | Ba phiên bản `addBonus()` | Cài đặt trong `Employee`, cùng cộng vào `monthlyBonus` |
| A.6 | Ghi đè tính lương, loại nhân viên và hiển thị | Ba phương thức thuần ảo trong `Employee`, dùng `override` trong lớp dẫn xuất |
| A.7 | Thêm, tìm, tổng hợp, tìm người lương cao nhất, hiển thị | Cài đặt trong `Payroll`, dùng lời gọi qua `Employee` |
| A.8 | Giải thích các quyết định thiết kế | Các mục 6-11 bên dưới |
| A.9 | Sơ đồ lớp đủ thuộc tính, truy cập, constructor, phương thức, bội số | `SoDoLop.svg` và `SoDoLop.mmd` |
| B.1 | Đóng gói, thưởng, phương thức đặt lại thưởng | Dữ liệu `private`, getter, `resetMonthlyBonus()` |
| B.2 | Lương cố định và phụ cấp không âm, hiển thị đầy đủ | `SalariedEmployee` |
| B.3 | Giờ thường, giờ vượt 160, không lưu tiền làm thêm dư thừa | `HourlyEmployee`, tính giờ và tiền trực tiếp từ trạng thái |
| B.4 | Kiểm tra doanh số, hoa hồng; cập nhật doanh số có kiểm soát | `SalesEmployee::setSalesRevenue()` |
| B.5 | Mã không trùng, đa hình, các phép tổng hợp, danh sách rỗng | `Payroll` và các kiểm thử tương ứng |
| C | Bốn nhân viên mẫu, các tổng mong đợi, ít nhất 10 tình huống | `main.cpp` và 42 kiểm thử trong `tests/TestPayroll.cpp` |

Đề không yêu cầu giao diện đồ họa, menu nhập liệu, lưu tệp hoặc tính thuế. Chương trình mẫu chạy trực tiếp với dữ liệu được chỉ định trong đề.

## 2. Đối tượng, trách nhiệm và quan hệ

| Lớp | Trách nhiệm | Dữ liệu riêng | Lý do tồn tại |
| --- | --- | --- | --- |
| `Employee` | Giữ định danh, thông tin chung, quản lý thưởng và khai báo hành vi chung | `employeeId`, `fullName`, `department`, `monthlyBonus` | Tập trung các bất biến chung, tránh viết lại thưởng trong từng loại nhân viên |
| `SalariedEmployee` | Tính và trình bày thu nhập nhân viên hưởng lương tháng | `monthlySalary`, `responsibilityAllowance` | Có thành phần thu nhập và công thức riêng |
| `HourlyEmployee` | Tính và trình bày thu nhập theo giờ, gồm làm thêm | `hourlyRate`, `workedHours` | Có quy tắc ngưỡng 160 giờ và hệ số 1,5 |
| `SalesEmployee` | Tính và trình bày thu nhập kinh doanh, cập nhật doanh số | `baseSalary`, `salesRevenue`, `commissionRate` | Có doanh số và hoa hồng riêng |
| `Payroll` | Quản lý danh sách của một kỳ lương, tổng hợp và tìm kiếm | `period`, `employees` | Tổng hợp nhiều nhân sự, không phải một loại nhân sự |

Ba lớp dẫn xuất có quan hệ **is-a** với `Employee`: một nhân viên theo giờ là một nhân viên. `Payroll` có quan hệ **has-a** với danh sách nhân viên, vì vậy không kế thừa `Employee`.

Mỗi lớp tập trung vào một trách nhiệm nghiệp vụ. Việc hiển thị được đặt trong các lớp nhân sự vì đề trực tiếp yêu cầu ghi đè `displayPayrollInfo()`. Với ứng dụng lớn hơn có nhiều giao diện, có thể tách phần trình bày; trong bài này chưa cần thêm lớp.

Các lớp dẫn xuất chỉ dùng dữ liệu chung qua getter và phương thức được cung cấp. Mọi thuộc tính đều là `private`; không sử dụng `protected` để cho phép lớp con tự sửa thưởng hoặc mã nhân viên. Hai hàm kiểm tra và hàm hiển thị thông tin chung là `protected` để lớp con tái sử dụng.

Không cần thêm `Interface` riêng: lớp trừu tượng `Employee` đã cung cấp hợp đồng chung cho bảng lương.

## 3. Bất biến và kiểm tra dữ liệu

| Dữ liệu | Điều kiện |
| --- | --- |
| Mã, họ tên, phòng ban | Không rỗng và không chỉ chứa khoảng trắng thông thường |
| `monthlyBonus` | Khởi tạo 0, không âm; chỉ thay đổi bằng thưởng hợp lệ hoặc đặt lại 0 |
| Lương tháng, phụ cấp, đơn giá giờ, lương cơ bản, doanh số | Hữu hạn và không âm |
| `workedHours` | Từ 0 đến 250, kể cả hai đầu mút |
| `commissionRate` | Từ 0 đến 0,3, kể cả hai đầu mút |
| Khoản thưởng cố định | Hữu hạn và lớn hơn 0 |
| Tỷ lệ thưởng | Lớn hơn 0 và không vượt 0,5 |
| Số tiền tham chiếu | Hữu hạn và lớn hơn 0 |
| Lý do thưởng, nếu có tham số này | Không rỗng và không chỉ có khoảng trắng |
| Mã trong một bảng lương | Không trùng, kể cả hai nhân viên thuộc hai loại khác nhau |

Kiểm tra số hữu hạn bổ sung việc loại bỏ `NaN` và vô cực. Chỉ kiểm tra `value < 0` là chưa đủ, vì phép so sánh với `NaN` không cho kết quả như số thông thường.

Mã nhân viên dùng `const std::string`, vì thay đổi mã sau khi thêm vào bảng lương có thể phá vỡ điều kiện không trùng. Các cập nhật có kiểm tra được thực hiện trước khi gán. Khi `setSalesRevenue()` nhận số âm hoặc khi thêm thưởng không hợp lệ, giá trị cũ giữ nguyên.

Constructor hoặc tham số nghiệp vụ không hợp lệ gây `std::invalid_argument`. Nếu tổng thưởng bị tràn miền biểu diễn `double`, gây `std::overflow_error` và giữ tổng thưởng cũ. Thêm mã trùng hoặc con trỏ rỗng vào `Payroll` trả `false`.

## 4. Nạp chồng constructor

Các constructor được triển khai như sau. Tham số chuỗi trong mã C++ dùng `const std::string&`.

| Lớp | Constructor rút gọn | Constructor đầy đủ |
| --- | --- | --- |
| `Employee` | `(employeeId, fullName)` | `(employeeId, fullName, department)` |
| `SalariedEmployee` | `(employeeId, fullName, monthlySalary)` | `(employeeId, fullName, department, monthlySalary, responsibilityAllowance)` |
| `HourlyEmployee` | `(employeeId, fullName, hourlyRate)` | `(employeeId, fullName, department, hourlyRate, workedHours)` |
| `SalesEmployee` | `(employeeId, fullName, baseSalary)` | `(employeeId, fullName, department, baseSalary, salesRevenue, commissionRate)` |

Constructor rút gọn dùng `department = "Unassigned"`. Phụ cấp chưa được cung cấp bằng 0; số giờ chưa được ghi nhận bằng 0; doanh số và tỷ lệ hoa hồng chưa có dữ liệu bằng 0. Thưởng luôn được lớp cơ sở khởi tạo bằng 0, rồi ghi nhận bằng `addBonus()`.

Ví dụ:

```cpp
SalariedEmployee::SalariedEmployee(const std::string& employeeId,
                                   const std::string& fullName, double monthlySalary)
    : SalariedEmployee(employeeId, fullName, "Unassigned", monthlySalary, 0) {
}
```

Đây là **delegating constructor - constructor ủy quyền**. Nó chuyển công việc khởi tạo và kiểm tra cho constructor đầy đủ, thay vì sao chép các câu kiểm tra. Constructor đầy đủ của lớp dẫn xuất gọi constructor của `Employee` để kiểm tra phần dữ liệu chung.

`Employee` vẫn có hai constructor dù là lớp trừu tượng: constructor của lớp cơ sở được chạy khi tạo đối tượng lớp dẫn xuất. Lớp trừu tượng không đồng nghĩa với việc không có constructor.

## 5. Công thức tính thu nhập

`SalariedEmployee`:

```text
grossPay = monthlySalary + responsibilityAllowance + monthlyBonus
```

`HourlyEmployee`:

```text
regularHours = min(workedHours, 160)
overtimeHours = max(workedHours - 160, 0)
grossPay = regularHours * hourlyRate
         + overtimeHours * hourlyRate * 1.5
         + monthlyBonus
```

Cách viết này đúng cho cả hai nhánh trong đề. Nếu làm 150 giờ, số giờ làm thêm là 0. Nếu làm 170 giờ, có 160 giờ thường và 10 giờ làm thêm. Không lưu riêng tiền làm thêm hoặc thu nhập tổng, vì chúng tính được từ trạng thái và có thể lỗi thời sau khi thưởng thay đổi.

`SalesEmployee`:

```text
grossPay = baseSalary + salesRevenue * commissionRate + monthlyBonus
```

Tỷ lệ dùng dạng thập phân: `0.05` tương ứng 5%. Không truyền `5` để biểu diễn 5%.

## 6. Vì sao dùng Overloading và Overriding?

**Overloading - nạp chồng:** nhiều phương thức cùng tên nhưng khác danh sách tham số. `addBonus()` diễn tả cùng một nghiệp vụ ghi nhận thưởng, trong ba cách cung cấp dữ liệu. Không cần đặt ba tên rời rạc cho cùng thao tác.

| Lời gọi trong `main.cpp` | Phiên bản được chọn | Lý do |
| --- | --- | --- |
| `e1->addBonus(1000000)` | `addBonus(double amount)` | Một đối số số; giá trị nguyên chuyển sang `double` |
| `e2->addBonus(500000, "Ho tro khach hang")` | `addBonus(double amount, const string& reason)` | Hai đối số, gồm khoản tiền và lý do |
| `e4->addBonus(0.02, 50000000, "Hoan thanh chi tieu")` | `addBonus(double rate, double referenceAmount, const string& reason)` | Ba đối số, gồm tỷ lệ, số tiền tham chiếu và lý do |

Lựa chọn overload diễn ra **khi biên dịch**, dựa vào số lượng, kiểu đối số và các chuyển đổi hợp lệ. Ba phiên bản đều là phương thức không `virtual` trong lớp cơ sở; loại thực tế của nhân viên không thay đổi ý nghĩa ghi nhận thưởng.

**Overriding - ghi đè:** lớp dẫn xuất cung cấp thực hiện riêng cho phương thức ảo được khai báo trong lớp cơ sở. `calculateGrossPay()` không cần nhận ba bộ tham số khác nhau: mỗi đối tượng đã giữ các dữ liệu cần cho công thức của nó.

```cpp
double Payroll::calculateTotalPayroll() const {
    double total = 0;
    for (const auto& employee : employees) {
        total += employee->calculateGrossPay();
    }
    return total;
}
```

`employee` là con trỏ thông minh đến `Employee`, nhưng đối tượng có thể là `HourlyEmployee`, `SalesEmployee` hoặc `SalariedEmployee`. Do phương thức là `virtual`, lời gọi chọn thực hiện tương ứng với **kiểu động của đối tượng**; đây là đa hình tại thời điểm chạy. `override` giúp trình biên dịch kiểm tra lớp con có thật sự ghi đè đúng chữ ký, gồm cả `const`, hay không.

Trong C++, overload chỉ khác kiểu trả về không tạo được hai phương thức độc lập. Vì vậy không thể tạo ba công thức tính lương bằng cách giữ cùng danh sách tham số rồi chỉ đổi kiểu trả về.

## 7. Lưu tổng thưởng hay lịch sử thưởng?

Chọn **chỉ lưu `monthlyBonus`**. Đề chỉ dùng tổng thưởng để tính thu nhập và cho phép chọn một trong hai cách. Mỗi phiên bản có `reason` vẫn kiểm tra lý do theo yêu cầu, nhưng không lưu lại nội dung đó.

Ưu điểm: dữ liệu và triển khai gọn, không phải quản lý thêm bản ghi. Hạn chế: không thể truy lại từng khoản thưởng hoặc lý do đã ghi nhận. Nếu bổ sung yêu cầu kiểm toán sau này, có thể thêm `BonusRecord` gồm khoản tiền và lý do, lưu bằng `vector<BonusRecord>`; không dùng các mảng song song.

`resetMonthlyBonus()` đặt tổng về 0 khi cần bắt đầu ghi nhận thưởng lại. Mỗi `Payroll` trong thiết kế hiện tại đại diện cho một kỳ lương; bài không bổ sung quy trình chuyển kỳ và lưu lịch sử nhiều tháng.

## 8. Payroll nên giữ nhân viên như thế nào?

Vấn đề cần tránh là **object slicing - cắt mất phần đối tượng dẫn xuất** khi sao chép đối tượng con thành giá trị lớp cơ sở. Trong thiết kế này, `Employee` trừu tượng nên không thể dùng `vector<Employee>` để lưu những đối tượng như vậy. Nếu `Employee` là lớp cụ thể, lưu giá trị kiểu cơ sở vẫn làm mất phần dữ liệu và hành vi của lớp con.

Ba phương án giữ được đa hình:

| Phương án | Quan hệ và quyền sở hữu | Ưu điểm | Nhược điểm | Khi nên dùng |
| --- | --- | --- | --- | --- |
| `vector<unique_ptr<Employee>>` | `Payroll` sở hữu độc quyền các nhân viên; Composition - hợp thành | Tự giải phóng, quyền sở hữu rõ, không slicing | Không dùng chung một đối tượng giữa nhiều bảng lương; việc chuyển vào tiêu thụ quyền sở hữu | Bảng lương sở hữu các đối tượng của kỳ hiện tại; chọn cho bài này |
| `vector<Employee*>` hoặc `reference_wrapper<Employee>` | Liên kết không sở hữu; Aggregation/Association tùy mô hình | Tái sử dụng nhân sự tồn tại độc lập, có thể được nhiều bảng lương tham chiếu | Bên ngoài phải bảo đảm vòng đời, có nguy cơ con trỏ treo | Có kho nhân sự riêng tồn tại lâu hơn các bảng lương |
| `vector<shared_ptr<Employee>>` | Nhiều nơi cùng sở hữu | Dễ chia sẻ đối tượng và giữ vòng đời | Có chi phí quản lý sở hữu; cập nhật thưởng trên đối tượng chung ảnh hưởng các bảng lương dùng nó | Thật sự cần sở hữu chia sẻ và đã làm rõ trạng thái theo kỳ |

Về **Simplicity** và **Maintainability**, `unique_ptr` phù hợp vì quyền sở hữu chỉ ở một nơi. Về **Flexibility** và **Reusability**, liên kết không sở hữu hoặc `shared_ptr` cho phép tái sử dụng cùng đối tượng, nhưng cần thiết kế trạng thái theo kỳ rõ hơn. Cả ba đều có **Extensibility** và **Testability** tốt khi chỉ gọi hợp đồng `Employee`. Về **Performance**, `shared_ptr` có thêm chi phí đếm tham chiếu; `unique_ptr` và con trỏ thường nhẹ hơn. Về **Complexity**, lựa chọn không sở hữu chuyển trách nhiệm vòng đời sang bên ngoài.

Chọn phương án đầu tiên vì đề w04 không yêu cầu cùng một đối tượng nhân viên được nhiều bảng lương sử dụng đồng thời. Yêu cầu nhân sự độc lập với nhóm dự án của Lab03-04 thuộc mô hình `ProjectTeam`; không mặc định áp dụng ràng buộc đó cho bài này.

`addEmployee()` nhận `unique_ptr<Employee>` bằng giá trị. Để chuyển vào một con trỏ đã có, gọi `std::move()`. Khi thêm thành công, `Payroll` giữ đối tượng; nếu bị từ chối, đối tượng đã chuyển vào được hủy khi hàm kết thúc. Con trỏ trả từ tìm kiếm là liên kết không sở hữu, không được `delete`.

Trong sơ đồ, một `Payroll` có **0..*** `Employee`; một đối tượng `Employee` thuộc **0..1** `Payroll` sở hữu. Trạng thái 0 thể hiện đối tượng mới tạo, chưa được chuyển vào bảng lương.

Destructor của `Employee` là `virtual`, để khi `unique_ptr<Employee>` hủy một đối tượng lớp con, destructor tương ứng chạy đầy đủ. Không cần tự viết `delete` trong `Payroll`.

## 9. Employee cụ thể hay trừu tượng?

Chọn **abstract class - lớp trừu tượng**. `Employee` cung cấp dữ liệu và hành vi thưởng dùng chung, nhưng bản thân tên gọi nhân viên chung không xác định một công thức tính thu nhập theo đề.

Ba phương thức `calculateGrossPay()`, `getEmployeeType()` và `displayPayrollInfo()` là thuần ảo (`= 0`). Lớp con phải triển khai chúng trước khi có thể tạo đối tượng. Điều này tránh vô tình tính lương một loại chưa được xác định bằng công thức mặc định 0.

Nếu đề bổ sung loại nhân viên thông thường có công thức rõ ràng, có thể tạo một lớp dẫn xuất cho loại đó. Không cần làm lớp cơ sở cụ thể chỉ để tạo được một nhân viên chưa biết cách tính lương.

## 10. Nhân viên kinh doanh đồng thời được trả theo giờ

Kế thừa đơn vẫn có thể biểu diễn một lớp `HourlySalesEmployee : public Employee`, với dữ liệu và công thức kết hợp. Tuy nhiên, cây phân loại hiện tại không giúp tự động tái sử dụng cả hai công thức giờ làm và hoa hồng.

Ba hướng có thể xét:

| Hướng | Ý tưởng | Ưu điểm | Hạn chế |
| --- | --- | --- | --- |
| Lớp mới kế thừa trực tiếp `Employee` | Tự kết hợp tiền giờ, hoa hồng và thưởng | Đơn giản khi chỉ có một loại kết hợp | Có thể lặp một phần công thức; nhiều tổ hợp tạo nhiều lớp |
| Kế thừa từ cả `HourlyEmployee` và `SalesEmployee` | Tái sử dụng hai lớp sẵn có | Bề ngoài có sẵn nhiều dữ liệu và hành vi | Có thể tạo hai phần cơ sở `Employee`, thưởng và định danh bị nhân đôi; phát sinh xung đột ghi đè |
| Composition với thành phần tính thu nhập | Nhân viên chứa các thành phần tiền giờ, hoa hồng hoặc chính sách trả lương | Ghép nhiều cách trả lương, giảm phụ thuộc vào một cây kế thừa cố định | Cần thêm thành phần và hợp đồng, phức tạp hơn cho bài nhỏ |

Khi có nhiều tổ hợp, Composition phù hợp hơn: phần tính giờ và phần hoa hồng có thể thay đổi độc lập, không buộc `Payroll` biết các tổ hợp cụ thể. Trong phạm vi hiện tại chỉ có ba loại theo đề nên giữ kế thừa đơn, chưa thêm các chính sách hoặc Design Pattern.

Ba lớp hiện tại đáp ứng hợp đồng của `Employee`: có thể dùng qua con trỏ cơ sở để tính và hiển thị thu nhập mà không phải kiểm tra loại. Đây là điều cần duy trì theo **Liskov Substitution Principle - nguyên lý thay thế Liskov** khi thêm lớp mới.

## 11. calculateTotalPayroll() có nên static không?

Không nên đặt `static` trong mô hình này. Tổng phụ thuộc danh sách `employees` của một đối tượng `Payroll` cụ thể. Hàm thành viên `static` không có `this` và không trực tiếp truy cập dữ liệu của một đối tượng.

Có thể viết một hàm `static` nhận danh sách làm tham số, nhưng lúc đó nó là tiện ích tính tổng cho dữ liệu được truyền vào. Không có lợi ích trong bài này so với `payroll.calculateTotalPayroll()`; dùng trạng thái toàn cục sẽ còn làm lẫn các kỳ lương.

## 12. Nếu dùng nhiều danh sách riêng cho từng loại?

Phải duy trì ba danh sách, kiểm tra trùng mã xuyên các danh sách, tổng hợp chúng trong các phép tìm kiếm và hiển thị, và thêm một danh sách khi có loại mới. Nếu mã tổng hợp viết trực tiếp các nhánh công thức theo loại, còn vi phạm yêu cầu không tính lương bằng chuỗi `if/else`.

Danh sách chung giữ một nguồn dữ liệu và các vòng lặp chung. Có thể lọc ra các nhóm để trình bày khi cần, thay vì biến chúng thành các cấu trúc quản lý độc lập.

## 13. Khi thêm ContractEmployee

Thêm `ContractEmployee.h` và `ContractEmployee.cpp`, kế thừa `Employee`, triển khai constructor và ba phương thức thuần ảo. Các phương thức thưởng và kiểm tra dữ liệu chung được tái sử dụng.

Sửa `main.cpp` hoặc phần tạo dữ liệu để khởi tạo loại mới; bổ sung kiểm thử và cập nhật sơ đồ. Nếu dùng `Makefile` hiện tại với danh sách tệp tường minh, thêm tệp triển khai mới vào `SOURCES` và header vào `HEADERS`.

Các thuật toán trong `Payroll.cpp` không cần đổi: tìm kiếm dùng mã, lọc dùng phòng ban, tổng và tìm người thu nhập cao nhất đều gọi `calculateGrossPay()` qua `Employee`. Đây là lợi ích của **Open/Closed Principle - nguyên lý mở/đóng** trong phần tổng hợp: mở rộng loại nhân sự qua lớp mới, giữ thuật toán bảng lương.

## 14. Thuật toán và các trường hợp rỗng

Với `n` nhân viên:

| Phương thức | Cách thực hiện | Thời gian |
| --- | --- | --- |
| `findEmployee()` | Duyệt đến khi gặp mã tương ứng | O(n) |
| `addEmployee()` | Tìm mã để chống trùng rồi thêm cuối vector | O(n), chi phí thêm cuối trung bình O(1) |
| `calculateTotalPayroll()` | Cộng lương từng nhân viên | O(n) |
| `calculatePayrollByDepartment()` | Lọc phòng ban và cộng lương | O(n) |
| `findHighestPaidEmployee()` | Giữ con trỏ tới người có lương lớn nhất đã gặp | O(n) |
| `displayPayroll()` | Gọi hiển thị từng nhân viên và tính tổng | O(n) |

Các mức trên tính theo số nhân viên, coi chi phí so sánh định danh là hằng số theo kích thước dữ liệu của bài. Bộ nhớ danh sách và nhân viên là O(n). Thêm liên tiếp `n` nhân viên bằng tìm tuyến tính có tổng chi phí O(n²); đủ đơn giản cho bài lab. Với dữ liệu lớn, có thể thêm chỉ mục `unordered_map` để tra mã, đổi lại phải duy trì nhất quán giữa chỉ mục và danh sách.

Danh sách rỗng: tổng bằng 0, tìm mã hoặc người thu nhập cao nhất trả `nullptr`, hiển thị thông báo chưa có nhân sự. Phòng ban không có nhân viên có tổng 0. Nếu thu nhập cao nhất bằng nhau, chọn người được thêm trước.

## 15. Dữ liệu mẫu và chứng minh kết quả

| Mã | Phép tính | Kết quả |
| --- | --- | ---: |
| E001 | 15.000.000 + 2.000.000 + 1.000.000 | 18.000.000 |
| E002 | 150 × 100.000 + 500.000 | 15.500.000 |
| E003 | 160 × 100.000 + 10 × 100.000 × 1,5 | 17.500.000 |
| E004 | 8.000.000 + 200.000.000 × 0,05 + 50.000.000 × 0,02 | 19.000.000 |

Tổng bảng lương: **70.000.000**. Tổng phòng Hỗ trợ, gồm E002 và E003: **33.000.000**. Người có thu nhập cao nhất: **E004 - Phạm Quốc Dũng**, thu nhập **19.000.000**.

Luồng chạy: tạo bảng lương kỳ `2026-09`; tạo bốn đối tượng dẫn xuất; ghi nhận ba cách thưởng; chuyển từng đối tượng vào bảng lương; hiển thị đa hình; tính tổng phòng; tìm người thu nhập cao nhất và tra mã E002. Khi kết thúc, con trỏ thông minh tự giải phóng các đối tượng.

## 16. Kiểm thử

`tests/TestPayroll.cpp` là chương trình kiểm thử riêng, có 42 kiểm tra kết quả. Một số kiểm tra nhóm nhiều dữ liệu không hợp lệ thuộc cùng một quy tắc. Kiểm thử so sánh thu nhập số và kiểm tra ngoại lệ, không chỉ hiển thị để quan sát bằng mắt.

| Số kiểm thử | Tình huống | Kết quả mong đợi |
| --- | --- | --- |
| 1-4 | Bốn nhân viên mẫu | 18.000.000; 15.500.000; 17.500.000; 19.000.000 |
| 5-7 | Tổng bảng, tổng Hỗ trợ, người cao nhất | 70.000.000; 33.000.000; E004 |
| 8-10 | Tìm mã qua đối tượng thường và `const`, mã thiếu, phòng thiếu | Tìm đúng; `nullptr`; tổng 0 |
| 11-13 | Ba constructor rút gọn | `Unassigned`, thưởng 0 và các mặc định đúng |
| 14-15 | Cộng ba cách thưởng rồi đặt lại | Tổng 400, sau đặt lại là 0 |
| 16 | Làm 0 giờ | Thu nhập 0 |
| 17 | Làm đúng 160 giờ | 16.000.000, không làm thêm |
| 18 | Làm 160,5 giờ | 16.075.000 |
| 19 | Làm đúng 250 giờ | 29.500.000 |
| 20 | Giờ -1 và 250,1 | Từ chối |
| 21-22 | Mã, tên, phòng rỗng hoặc chỉ có khoảng trắng | Từ chối |
| 23 | Lương, phụ cấp, đơn giá, doanh số âm | Từ chối |
| 24 | Hoa hồng 0 và 0,3 | Chấp nhận; thu nhập 8.000.000 và 68.000.000 |
| 25 | Hoa hồng -0,01 và 0,301 | Từ chối |
| 26-27 | Thưởng cố định không dương, lý do trống | Từ chối |
| 28 | Thưởng bằng 0,5 × 1.000 | Chấp nhận, cộng 500 |
| 29-31 | Tỷ lệ ngoài khoảng, tham chiếu không dương, lý do trống | Từ chối |
| 32 | Kiểm tra sau các thưởng không hợp lệ | Tổng thưởng vẫn 500 |
| 33-34 | Cập nhật doanh số 300.000.000, rồi thử doanh số âm | Thu nhập 23.000.000; cập nhật sai giữ giá trị cũ |
| 35 | `NaN` và vô cực | Từ chối |
| 36 | Nhân viên khác loại cùng mã E001 | Không thêm; số lượng 4 và tổng 70.000.000 giữ nguyên |
| 37 | Thêm con trỏ rỗng | Không thêm |
| 38 | Bảng lương rỗng | Tổng 0, kết quả tìm `nullptr`, thông báo đúng |
| 39 | Hai người cùng lương | Chọn người thêm trước |
| 40 | Thêm 10.000.000 thưởng cho E002 sau khi vào bảng lương | Tổng 80.000.000; Hỗ trợ 43.000.000; người cao nhất E002 |
| 41 | Kỳ lương rỗng hoặc chỉ có khoảng trắng | Từ chối |
| 42 | Cộng thưởng vượt miền biểu diễn | Báo tràn số, giữ tổng cũ |

Kết quả thực thi: **42/42 PASS**. Mã biên dịch với C++11, `-Wall -Wextra -Wpedantic -Werror`. Chạy AddressSanitizer và UndefinedBehaviorSanitizer không báo lỗi; kiểm tra rò rỉ của LeakSanitizer không chạy được do hạn chế truy cập `/proc` của môi trường, nên tắt riêng chức năng này bằng `detect_leaks=0`.

## 17. Sơ đồ lớp

Mở `SoDoLop.svg` bằng trình duyệt để xem sơ đồ hoàn chỉnh; có thể phóng to mà không giảm chất lượng. `SoDoLop.mmd` chứa mã Mermaid tương ứng.

Ký hiệu: `+` là `public`, `-` là `private`, `#` là `protected`; `abstract` là phương thức thuần ảo, `override` là phương thức ghi đè. Kim cương đen ở `Payroll` thể hiện sở hữu độc quyền danh sách nhân viên. Bội số là `Payroll 0..1` và `Employee 0..*`.
