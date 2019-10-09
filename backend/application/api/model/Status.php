<?php
/**
 * FileName: Status.php
 * Product: Lazy OJ
 * Author: Hu Lang
 * DateTime: 2019/9/27 13:08
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * Description:
 *
 */


namespace app\api\model;


use think\Model;

class Status extends Model
{

    protected $pk = 'sid';
    protected $table = 'solution';
    protected $autoWriteTimestamp = true;

    public function getUidAttr($value) {
        $user = new User();
        return $user->get($value)->username;
    }

    public function getResultAttr($value)
    {
        $map = [
            0 => '等待',
            1 => '等待重判',
            2 => '编译中',
            3 => '评测中',
            4 => '正确',
            5 => '格式错误',
            6 => '答案错误',
            7 => '时间超限',
            8 => '内存超限',
            9 => '输出超限',
            10 => '运行错误',
            11 => '编译错误'
        ];
        return $map[$value];
    }

    public function getLanguageAttr($value) {
        $map = [
            0 => 'C',
            1 => 'C++',
            2 => 'Pascal',
            3 => 'Java',
            4 => 'Ruby',
            5 => 'Bash',
            6 => 'Python',
            7 => 'PhP',
            8 => 'Perl',
            9 => 'C#',
            10 => 'Object-c',
            11 => 'FreeBasic',
            12 => 'Scheme',
            13 => 'Clang',
            14 => 'Clang++',
            15 => 'Lua',
            16 => 'JavaScript',
            17 => 'Go',
            18 => 'SQL(sqlite3)'
        ];
        return $map[$value];
    }

    public function setLanguageAttr($value) {
        $val = strtolower($value);
        $map = [
            'c' => 0,
            'cpp' => 1,
            'pascal' => 2,
            'java' => 3,
            'ruby' => 4,
            'bash' => 5,
            'python' => 6,
            'php' => 7,
            'perl' => 8,
            'c#' => 9,
            'object-c' => 10,
            'freebasic' => 11,
            'scheme' => 12,
            'clang' => 13,
            'clang++' => 14,
            'lua' => 15,
            'javascript' => 16,
            'go' => 17,
            'sql(sqlite3)' => 18
        ];
        return $map[$value];
    }

}
